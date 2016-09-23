#pragma once

#include <vector>

enum class Tile;
class Meld;
class Pair;

class TileHolder
{
public:
	void add(Tile tile);
	void add(Meld meld);
	bool empty() const;

	bool isNextTilePair() const;
	bool isNextTilePonOrKan() const;
	bool isNextTileChii() const;

	Pair popNextPair();
	Meld popNextPonOrKan();
	Meld popNextChii();

private:
	std::vector<Tile> tiles;
	std::vector<Meld> melds;
};
