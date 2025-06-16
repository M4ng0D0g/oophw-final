#pragma once

#include "Unit.h"
#include "object/Tile.h"
#include "object/Score.h"
#include "GameConfig.h"
#include "view/icon/IconFactory.h"
#include <vector>
#include <memory>

class Model {
private:
	const GameConfig& config_;
	bool updating_ = false;

	Vector2<Tile::Ptr> board_;
	Tile::Type boardType_ = Tile::Type::REAL;
	Tile::Sign boardSign_ = Tile::Sign::POSITIVE;
	bool converseType_ = false;
	bool converseSign_ = false;

	Score score_;
	long long steps_ = 0;

	bool handleMerge(int&, int&, const Pos2&, Tile::Ptr&, Tile::Ptr&, int, Direction);

public:
	Model(const GameConfig& config);

	void initialize();
	void resetStatus();
	void updateStatus();
	void notUpdateStatus();

	bool isUpdating() const {
		return updating_;
	}

	const Vector2<Tile::Ptr>& getBoard() const {
		return board_;
	}
	const Tile::Type getBoardType() const {
		return boardType_;
	}
	const Tile::Sign getBoardSign() const {
		return boardSign_;
	}
	bool isStucked() const;
	void converseBoard();

	bool moveTiles(Direction);
	Tile::Ptr summonTile() const;
	void placeTile(Direction, Tile::Ptr);
	void updateIcon(Tile::Ptr tile) const {
		auto icon = IconFactory::create(tile);
		tile->setIcon(icon);
	}

	// Score
	const Score& getScore() const {
		return score_;
	}
};