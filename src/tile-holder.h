#pragma once

#include <vector>
#include <utility>
#include <functional>

enum class Tile;

class TileHolder
{
	using Meld = std::vector<Tile>;

public:
	void add(Tile tile);
	bool empty() const;

	bool isNextTilePair() const;
	bool isNextTilePon() const;
	bool isNextTileChii() const;

	Meld popNextPair();
	Meld popNextPon();
	Meld popNextChii();

private:
	std::vector<Tile> tiles;
};
