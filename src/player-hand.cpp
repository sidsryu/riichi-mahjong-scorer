#include "player-hand.h"
#include "tile-functor.h"
#include "tile-holder.h"
#include "meld.h"
#include <cassert>

using namespace std;

void PlayerHand::add(Tile tile)
{
	tiles.insert(tile);
	last_tile = tile;
}

void PlayerHand::remove(Tile tile)
{
	assert(0 < tiles.count(tile));

	auto it = tiles.find(tile);
	tiles.erase(it);
}

void PlayerHand::bindSequence(BindTiles tiles)
{
	assert(3 == tiles.size());
	assert(IsSame()(NextTile()(tiles[0]), tiles[1]));
	assert(IsSame()(NextTile()(tiles[1]), tiles[2]));

	for (auto it : tiles)
	{
		remove(it);
	}

	melds.push_back({ tiles, true });
}

void PlayerHand::bindTriplet(BindTiles tiles)
{
	assert(3 == tiles.size());
	assert(IsSame()(tiles[0], tiles[1]));
	assert(IsSame()(tiles[0], tiles[2]));

	for (auto it : tiles)
	{
		remove(it);
	}

	melds.push_back({ tiles, true });
}

void PlayerHand::bindOpenQuad(BindTiles tiles)
{
	assert(4 == tiles.size());
	assert(IsSame()(tiles[0], tiles[1]));
	assert(IsSame()(tiles[1], tiles[2]));
	assert(IsSame()(tiles[2], tiles[3]));

	for (auto it : tiles)
	{
		remove(it);
	}

	melds.push_back({ tiles, true });
}

void PlayerHand::bindClosedQuad(BindTiles tiles)
{
	assert(4 == tiles.size());
	assert(IsSame()(tiles[0], tiles[1]));
	assert(IsSame()(tiles[1], tiles[2]));
	assert(IsSame()(tiles[2], tiles[3]));

	for (auto it : tiles)
	{
		remove(it);
	}

	melds.push_back({ tiles, false });
}

bool PlayerHand::isClosedHand() const
{
	for (auto it : melds)
	{
		if (it.isOpen()) return false;
	}

	return true;
}

Tile PlayerHand::lastTile() const
{
	return last_tile;
}

TileHolder PlayerHand::makeHandHolder() const
{
	TileHolder h;

	for (auto it : tiles)
	{
		h.add(it);
	}

	for (auto it : melds)
	{
		h.add(it);
	}

	return h;
}
