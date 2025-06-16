#pragma once

#include "Unit.h"
#include "view/AnsiPrint.h"
#include <vector>
#include <string>

struct Cell{
    AnsiColor::Ptr color;
    std::string ascii;
    Cell(AnsiColor::Ptr c, std::string a) : color(c), ascii(a){}
};

using Icon = Vector2<Cell>;

size_t icon_width(const Icon& icon);

size_t icon_height(const Icon& icon); 

