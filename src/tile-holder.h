#pragma once

#include <vector>
#include <set>

enum class Tile;
class Meld;
class Pair;

class TileHolder
{
public:
	void add(Tile tile);
	void add(Meld meld);
	bool empty() const;

	Pair popPairWithFrontTile();
	Meld popTripletOrQuadWithFrontTile();
	Meld popSequenceWithFrontTile();

private:
	std::vector<Tile> popTiles(std::set<int> indices);
	Meld popTripletOrQuadMeld();
	Meld popSequenceMeld();

private:
	std::vector<Tile> tiles;
	std::vector<Meld> melds;
};
