#pragma once

#include "Icon.h"
#include "model/object/Tile.h"

class IconFactory {
public:
	static Icon create(Tile::Ptr);
};