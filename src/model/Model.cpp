#include "model/Model.h"
#include <stdlib.h>
#include <unordered_map>
#include <iostream>

static const std::unordered_map<Direction, Pos2> deltaMap = {
	{Direction::UP, {0, -1}},
	{Direction::DOWN, {0, 1}},
	{Direction::LEFT, {-1, 0}},
	{Direction::RIGHT, {1, 0}}
};

// ---------------------------------------------------------------- //

Model::Model(const GameConfig& config) : config_(config) {
	board_ = Vector2<Tile::Ptr>(
		config_.fieldSize.height, Vector1<Tile::Ptr>(config_.fieldSize.width, nullptr)
	);
}

void Model::initialize() {
	for(int i = 0; i < 2; ++i) {
		auto tile = summonTile();
		placeTile(Direction::STOP, tile);
	}
}

void Model::resetStatus() {
	// 重製合併狀態
	for(int y = 0; y < config_.fieldSize.height; ++y) {
		for(int x = 0; x < config_.fieldSize.width; ++x) {
			auto& tile = board_[y][x];
			if(tile != nullptr) tile->setCombined(false);
		}
	}
}

void Model::updateStatus() {
	// 根據合併狀態修改運算子
	for(int y = 0; y < config_.fieldSize.height; ++y) {
		for(int x = 0; x < config_.fieldSize.width; ++x) {
			auto& tile = board_[y][x];
			if(tile == nullptr) continue;

			auto combined = tile->getCombined();
			auto op = tile->getOp();
			if(combined && op == Tile::Operator::PLUS) {
				tile->setOp(Tile::Operator::MULTIPLY);
				updateIcon(tile);
			}	
			else if(!combined && op == Tile::Operator::MULTIPLY) {
				tile->setOp(Tile::Operator::PLUS);
				updateIcon(tile);
			}
		}
	}
}

void Model::notUpdateStatus() {
}

bool Model::isStucked() const {
	// 檢查是否全部無法合成
	for(int y = 0; y < config_.fieldSize.height; ++y) {
		for(int x = 0; x < config_.fieldSize.width; ++x) {
			if(board_[y][x] == nullptr) return false;

			for(const auto& delta : deltaMap) {
				int dx = x + delta.second.x;
				int dy = y + delta.second.y;

				if(dx < 0 || dx >= config_.fieldSize.width || dy < 0 || dy >= config_.fieldSize.height)
					continue;
				
				if(board_[dy][dx] == nullptr) return false;
				if(board_[y][x]->isSame(board_[dy][dx])) return false;
			}
		}
	}

	return true;
}

void Model::converseBoard() {
	// 翻轉整個狀態
	if(converseSign_) boardSign_ = (boardSign_ == Tile::Sign::POSITIVE) ? Tile::Sign::NEGATIVE : Tile::Sign::POSITIVE;
	if(converseType_) boardType_ = (boardType_ == Tile::Type::REAL) ? Tile::Type::IMAGINARY : Tile::Type::REAL;

	for(int y = 0; y < config_.fieldSize.height; ++y) {
		for(int x = 0; x < config_.fieldSize.width; ++x) {
			auto& tile = board_[y][x];
			if(tile == nullptr) continue;
			if(converseSign_) tile->converse(1);
			if(converseType_) tile->converse(-1);
			updateIcon(tile);
		}
	}
}

// Tile
bool Model::moveTiles(Direction dir) {
	// 初始化翻轉
	converseSign_ = false;
	converseType_ = false;
	
	// 根據方向設定迴圈參數
	const auto delta = deltaMap.at(dir);
	// std::cout << "flag" << std::endl;

	const int width = config_.fieldSize.width;
	const int height = config_.fieldSize.height;

	int outer = (delta.y != 0) ? width : height;
	int inner = (delta.y != 0) ? height : width;

	int innerStart = (delta.x + delta.y < 0) ? 0 : inner - 1;
	int innerEnd = (delta.x + delta.y < 0) ? inner : -1;
	int step = (delta.x + delta.y < 0) ? 1 : -1;

	bool movedAny = false;

	for(int o = 0; o < outer; ++o) {
		int to = innerStart;
		int fr = innerStart;
		
		while(fr != innerEnd) {
			Pos2 frPos = (delta.y != 0) ? Pos2{o, fr} : Pos2{fr, o};
			Pos2 toPos = (delta.y != 0) ? Pos2{o, to} : Pos2{to, o};

			Tile::Ptr& tileFr = board_[frPos.y][frPos.x];
			Tile::Ptr& tileTo = board_[toPos.y][toPos.x];

			if(handleMerge(fr, to, toPos, tileFr, tileTo, step, dir)) movedAny = true;
		}
	}
	return movedAny;
}

bool Model::handleMerge(
	int& idxFr, int& idxTo, const Pos2& toPos,
	Tile::Ptr& tileFr, Tile::Ptr& tileTo,
	int step, Direction dir
) {
	// Fr無效
	if(idxFr == idxTo || tileFr == nullptr) {
		idxFr += step;
		return false;
	}

	// 移動
	if(tileTo == nullptr) {
		tileFr->setPosition(toPos);
		tileTo = tileFr;
		tileFr = nullptr;
		idxFr += step;
		return true;
	}

	// 不相同
	if(!tileTo->isSame(tileFr)) {
		idxTo += step;
		return false;
	}

	// 相同
	if(tileTo->getCategory() == Tile::Category::DIMENSION) {
		int result = tileTo->combine(dir);
		if(result == 1) converseSign_ = !converseSign_;
		else if(result == -1) converseType_ = !converseType_;
	}
	else {
		int multiCnt = 0
			+ (tileTo->getOp() == Tile::Operator::MULTIPLY)
			+ (tileFr->getOp() == Tile::Operator::MULTIPLY);

		if(multiCnt == 0) tileTo->operatePlus();
		else if(multiCnt == 1) tileTo->operateTime();
		else tileTo->operatePower();
	}
	tileFr = nullptr;
	tileTo->setCombined(true);
	updateIcon(tileTo);
	idxFr += step;
	idxTo += step;

	return true;
}

Tile::Ptr Model::summonTile() const {
	Tile::Sign sign = boardSign_;
	int power = 1;

	int rdTile = rand() % 10;
	if(rdTile == 0) sign = Tile::Sign::ZERO;
	else if(rdTile >= 1 && rdTile <= 3) power = 2;

	//測試用
	// if(rdTile >= 7 && rdTile <= 9) {
	// 	Tile::Ptr tile = Tile::create(Tile::Category::DIMENSION, boardType_, sign, power);
	// 	updateIcon(tile);
	// 	return tile;
	// }

	Tile::Ptr tile = Tile::create(Tile::Category::CONST, boardType_, sign, power);
	updateIcon(tile);
	return tile;
}

void Model::placeTile(Direction dir, Tile::Ptr tile) {
	Vector1<Pos2> spaces;

	auto check = [&](int x, int y) {
		if(board_[y][x] == nullptr) spaces.push_back({x, y});
	};

	const int width = config_.fieldSize.width;
	const int height = config_.fieldSize.height;

	if(dir == Direction::STOP) {
		for(int y = 0; y < height; ++y) {
			for(int x = 0; x < width; ++x) check(x, y);
		}
	} 
	else {
		const auto delta = deltaMap.at(dir);
		if(delta.x != 0) {
			int x = (delta.x > 0) ? 0 : width - 1;
			for(int y = 0; y < height; ++y) check(x, y);
		}
		else if(delta.y != 0) {
			int y = (delta.y > 0) ? 0 : height - 1;
			for(int x = 0; x < width; ++x) check(x, y);
		}
	}

	if(spaces.empty()) return;

	Pos2 pos = spaces[rand() % spaces.size()];
	board_[pos.y][pos.x] = tile;
	tile->setPosition({pos.x, pos.y});
}



