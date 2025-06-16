#include "model/object/Tile.h"
#include <limits.h>

Tile::Tile(Category c, Type t, Sign s, long long p)
: category_(c), type_(t), sign_(s), powerOf2_(p) {}

bool Tile::isSame(const Tile::Ptr other) const {
	if(category_ == Category::UNDEFINED || other->category_ == Category::UNDEFINED) return false;
	
	if(category_ != other->category_) return false;
	if(type_ != other->type_) return false;
	if(sign_ != other->sign_) return false;
	if(powerOf2_ != other->powerOf2_) return false;

	return true;
}

// Other
void Tile::operatePlus() {
	if(category_ != Category::CONST) return;
	if(sign_ == Sign::POSITIVE || sign_ == Sign::NEGATIVE) ++powerOf2_;
}

void Tile::operateTime() {
	if(category_ != Category::CONST) return;
	if(sign_ == Sign::POSITIVE || sign_ == Sign::NEGATIVE) powerOf2_ *= 2;
	
	if(type_ == Type::IMAGINARY) {
		type_ = Type::REAL;
		if(sign_ == Sign::POSITIVE) sign_ = Sign::NEGATIVE;
		else if(sign_ == Sign::POSITIVE) sign_ = Sign::NEGATIVE;
	}
	if(sign_ == Sign::NEGATIVE) sign_ = Sign::POSITIVE;
}

void Tile::operatePower() {
	if(category_ != Category::CONST) return;

	if(sign_ == Sign::ZERO) category_ = Category::DIMENSION;
	else if(sign_ == Sign::POSITIVE) {
		if(type_ == Type::REAL) powerOf2_ *= (1 << powerOf2_);
		else if(type_ == Type::IMAGINARY) category_ = Category::UNDEFINED;
	}
	else if(sign_ == Sign::NEGATIVE) {
		if(type_ == Type::REAL) {
			if(powerOf2_ != 0) sign_ = Sign::POSITIVE;
			powerOf2_ *= (1 << powerOf2_) * -1;
		}
		else if(type_ == Type::IMAGINARY) category_ = Category::UNDEFINED;
	}
}

// Converse P/N if return 1 
// Do nothing if return 0
// Converse R/i if return -1
int Tile::combine(Direction dir) {
	if(category_ == Category::DIMENSION) {
		if(dir == Direction::LEFT || dir == Direction::RIGHT) return 1;
		else if (dir == Direction::UP || dir == Direction::DOWN) return -1;
	}
	return 0;
}

void Tile::converse(int condition) {
	if(category_ == Category::UNDEFINED || category_ == Category::COUNT) return;
	if(condition == 1) sign_ = (sign_ == Sign::POSITIVE) ? Sign::NEGATIVE : Sign::POSITIVE;
	else if (condition == -1) type_ = (type_ == Type::REAL) ? Type::IMAGINARY : Type::REAL;
}


std::string Tile::toStr() {
	if(sign_ == Sign::ZERO) return "0";

	std::string str;
	if(sign_ == Sign::NEGATIVE) str += '-';

	if (powerOf2_ >= 32 || powerOf2_ < 0) str += "2^" + std::to_string(powerOf2_);
	else str += std::to_string(1 << powerOf2_);

	return str;
}
