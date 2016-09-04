#pragma once

#include <vector>

enum class Tile;

struct Meld
{
	std::vector<Tile> tiles;
	bool is_open { false };	
};

struct WiningHand
{
	std::vector<Meld> pairs;
	std::vector<Meld> melds;
};
