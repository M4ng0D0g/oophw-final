#include "view/icon/IconFactory.h"

#include <unordered_map>

// ◙▩▣

Icon IconFactory::create(Tile::Ptr tile) {
	AnsiColor::Ptr color;
	std::string str0 = "╔═══════════╗";
	std::string str1 = "║           ║";
	std::string str2 = "║           ║";
	std::string str3 = "║           ║";
	std::string str4 = "╚═══════════╝";

	auto cate = tile->getCategory();
	if(cate == Tile::Category::UNDEFINED) {
		str1 = "║           ║";
		str2 = "║ UNDEFINED ║";
		str3 = "║           ║";
		color = AnsiColor::RGB(50, 50, 50);
	}
	else {
		// str1 = R/i
		auto type = tile->getType();
		auto sign = tile->getSign();

		if(type == Tile::Type::REAL) {
			str1 = "║   ▣[R]▣   ║";
			if(sign == Tile::Sign::POSITIVE) color = AnsiColor::Basic(1);
			else if(sign == Tile::Sign::NEGATIVE) color = AnsiColor::Basic(4);
		}
		else if(type == Tile::Type::IMAGINARY) {
			str1 = "║   ▣[i]▣   ║";
			if(sign == Tile::Sign::POSITIVE) color = AnsiColor::Basic(3);
			else if(sign == Tile::Sign::NEGATIVE) color = AnsiColor::Basic(5);
		}
		if(sign == Tile::Sign::ZERO) {
			str1 = "║   ▣[-]▣   ║";
			color = AnsiColor::RGB(180, 180, 180);
		}

		// str2 = value
		auto str = tile->toStr();
		auto strSize = str.size();
		if(strSize > 11) str2 = "║  Exceed!  ║";
		else {
			int prefix = (11 - strSize) / 2;
			int suffix = (12 - strSize) / 2;
			str2 = "║" + std::string(prefix, ' ') + str + std::string(suffix, ' ') + "║";
		}

		// str3 = op
		auto op = tile->getOp();
		if(op == Tile::Operator::MULTIPLY) str3 = "║  !COMBO!  ║";

		// dimension
		if(cate == Tile::Category::DIMENSION) {
			str1 = "║     ⬆     ║";
			str2 = "║⬅ [DIMEN] ⮕║";
			str3 = "║     ⬇     ║";
		}
	}

	Icon icon = {
		{ Cell(color, str0) },
		{ Cell(color, str1) },
		{ Cell(color, str2) },
		{ Cell(color, str3) },
		{ Cell(color, str4) }
	};

	return icon;
}