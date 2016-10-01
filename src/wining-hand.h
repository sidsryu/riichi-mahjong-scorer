#pragma once

#include "tile-define.h"
#include <vector>

namespace mahjong {
class Pair;
class Meld;

struct WiningHand
{
	std::vector<Pair> pairs;
	std::vector<Meld> melds;
	std::vector<Tile> tiles;
	Tile last_tile;
};
}
