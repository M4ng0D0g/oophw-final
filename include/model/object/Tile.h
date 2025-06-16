#pragma once

#include "Unit.h"
#include "Viewable.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>

class Tile : public Viewable {
public:
	enum class Category  {
		UNDEFINED, CONST, DIMENSION, COUNT
	};
	enum class Type {
		REAL, IMAGINARY, COMPLEX, COUNT
	};
	enum class Sign {
		ZERO, NEGATIVE, POSITIVE, COUNT
	};
	enum class Operator {
		PLUS, MULTIPLY, COUNT
	};

	using Ptr = std::shared_ptr<Tile>;
	static Ptr create(Category category, Type type, Sign sign, long long powerOf2) {
		Tile* tile = nullptr;

		switch(category) {
			case Category::UNDEFINED:
				tile = new Tile(category, Type::COUNT, Sign::COUNT, 0);
				break;

			case Category::CONST:
				if(powerOf2 == 0) sign = Sign::ZERO;
				tile = new Tile(category, type, sign, powerOf2);
				break;

			case Category::DIMENSION:
				// DIMENSION 的 type/sign 只有顯示用途
				tile = new Tile(category, type, sign, 0);
				break;

			default:
				break;
		}
		if(tile != nullptr) tile->op_ = Operator::PLUS;
		
		return Ptr(tile);
	}

private:
	Tile(Category, Type, Sign, long long);

	Category category_;
	Type type_;
	Sign sign_;
	long long powerOf2_;
	Operator op_;
	Pos2 pos_;

	bool combined_ = false;

public:
	bool isSame(const Ptr other) const;

	// Getter
	Category getCategory() const {
		return category_;
	}
	Type getType() const {
		return type_;
	}
	Sign getSign() const {
		return sign_;
	}
	long long getPowerOf2() const {
		return powerOf2_;
	}
	Operator getOp() const {
		return op_;
	}
	const Pos2& getPosition() const override {
		return pos_;
	}
	bool getCombined() const {
		return combined_;
	}

	// Setter
	void setCategory(Category category) {
		category_ = category;
	}
	void setType(Type type) {
		type_ = type;
	}
	void setSign(Sign sign) {
		sign_ = sign;
	}
	void setPowerOf2(long long value) {
		powerOf2_ = value;
	}
	void setOp(Operator op) {
		op_ = op;
	}
	void setPosition(const Pos2& pos) override {
		pos_ = pos;
	}
	void setCombined(bool combined) {
		combined_ = combined;
	}
	
	// Other
	void operatePlus();
	void operateTime();
	void operatePower();
	int combine(Direction);
	void converse(int);

	std::string toStr();
};