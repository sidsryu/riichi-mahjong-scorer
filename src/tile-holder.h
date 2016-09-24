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
	bool isNextTileTripletOrQuad() const;
	bool isNextTileSequence() const;

	Pair popNextPair();
	Meld popNextTripletOrQuad();
	Meld popNextSequence();

private:
	std::vector<Tile> tiles;
	std::vector<Meld> melds;
};
