#pragma once

#include <vector>
#include <utility>
#include <functional>

enum class Tile;

class TileHolder
{
public:
	void add(Tile tile);
	bool empty() const;

	bool isNextTilePair() const;
	bool isNextTilePon() const;
	bool isNextTileChii() const;

	Tile popFront();
	void popFrontChii(std::function<void(Tile)> fn);

private:
	std::vector<Tile> tiles;
};
