#pragma once

#include <set>
#include <functional>
#include <vector>

enum class Tile;
class Meld;
class TileHolder;
class WiningState;

class PlayerHand
{
	using BindTiles = std::vector<Tile>;
	using FreeTiles = std::vector<Tile>;

	enum class ReadyType
	{
		not_ready = 0,
		ready_hand,
		double_ready,
	};	

public:
	void add(Tile tile);
	void remove(Tile tile);
	void bindSequence(BindTiles tiles);
	void bindTriplet(BindTiles tiles);
	void bindOpenQuad(BindTiles tiles);
	void bindClosedQuad(BindTiles tiles);
	void readyHand();
	void doubleReady();

	bool isClosedHand() const;
	Tile lastTile() const;
	int bonusTileCount(const WiningState& state) const;
	TileHolder makeHandHolder() const;
	FreeTiles makeFreeTiles() const;
	bool isReadyHand() const;
	bool isDoubleReady() const;

private:	
	Tile last_tile;
	std::multiset<Tile> tiles;
	std::vector<Meld> melds;
	ReadyType ready_type { ReadyType::not_ready };
};
