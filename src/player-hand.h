#pragma once

#include <set>
#include <functional>
#include <vector>

enum class Tile;
class Meld;
class TileHolder;

class PlayerHand
{
	using BindTiles = std::vector<Tile>;

public:
	void add(Tile tile);
	void remove(Tile tile);
	void bindSequence(BindTiles tiles);
	void bindTriplet(BindTiles tiles);
	void bindOpenQuad(BindTiles tiles);
	void bindClosedQuad(BindTiles tiles);

	bool isClaim() const;
	Tile lastTile() const;
	TileHolder makeHandHolder() const;

private:
	Tile last_tile;
	std::multiset<Tile> tiles;
	std::vector<Meld> melds;
};
