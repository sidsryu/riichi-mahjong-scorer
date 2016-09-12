#pragma once

#include <vector>
#include <utility>
#include <functional>

enum class Tile;
struct Meld;
struct Pair;

class TileHolder
{
public:
	void add(Tile tile);
	void add(Meld meld);
	bool empty() const;

	bool isNextTilePair() const;
	bool isNextTilePon() const;
	bool isNextTileChii() const;

	Pair popNextPair();
	Meld popNextPon();
	Meld popNextChii();

private:
	std::vector<Tile> tiles;
};
