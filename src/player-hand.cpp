#include "player-hand.h"
#include "tile-functor.h"
#include "tile-holder.h"
#include "meld.h"
#include "wining-state.h"
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
	Meld meld { tiles, true };	
	assert(meld.isSequence());

	for (auto it : tiles)
	{
		remove(it);
	}

	melds.push_back(meld);	
}

void PlayerHand::bindTriplet(BindTiles tiles)
{
	Meld meld { tiles, true };
	assert(meld.isTriplet());

	for (auto it : tiles)
	{
		remove(it);
	}

	melds.push_back(meld);
}

void PlayerHand::bindOpenQuad(BindTiles tiles)
{
	Meld meld { tiles, true };
	assert(meld.isQuad());

	for (auto it : tiles)
	{
		remove(it);
	}

	melds.push_back(meld);
}

void PlayerHand::bindClosedQuad(BindTiles tiles)
{
	Meld meld { tiles, false };
	assert(meld.isQuad());

	for (auto it : tiles)
	{
		remove(it);
	}

	melds.push_back(meld);
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

int PlayerHand::bonusTileCount(const WiningState& state) const
{
	auto bonus_tile_count { 0 };

	for (auto it : tiles)
	{
		if (IsRedFive()(it))
		{
			bonus_tile_count++;
		}

		if (state.isBonusTile(it))
		{
			bonus_tile_count++;
		}
	}

	for (const auto& it : melds)
	{
		bonus_tile_count += it.bonusTileCount(state);
	}

	return bonus_tile_count;
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
