#pragma once

#include <vector>
#include <utility>

enum class Tile;

struct Meld
{
	std::vector<Tile> tiles;
	bool is_open { false };

	Meld(std::vector<Tile> tiles, bool is_open)
		: tiles(tiles)
		, is_open(is_open)
	{}
};

struct Pair
{
	std::vector<Tile> tiles;

	Pair(std::vector<Tile> tiles)
		: tiles(tiles)
	{}
};

struct WiningHand
{
	std::vector<Pair> pairs;
	std::vector<Meld> melds;
	Tile last_tile;
};
