#include "player-hand.h"
#include "tile-functor.h"
#include "tile-holder.h"
#include "meld.h"
#include "wining-state.h"
#include <cassert>

using namespace std;

namespace mahjong {
void PlayerHand::add(Tile tile)
{
	tiles.insert(tile);
	last_tile = tile;
}

void PlayerHand::remove(Tile tile)
{
	assert(0 < tiles.count(tile));
	assert(ready_type == ReadyType::not_ready || last_tile == tile);

	auto it = tiles.find(tile);
	tiles.erase(it);
}

void PlayerHand::bindSequence(BindTiles tiles)
{
	assert(ready_type == ReadyType::not_ready);

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
	assert(ready_type == ReadyType::not_ready);

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
	assert(ready_type == ReadyType::not_ready);

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
	// NOTE: Allow bind closed quad in the ready, MUST not change waiting tiles.

	Meld meld { tiles, false };
	assert(meld.isQuad());

	for (auto it : tiles)
	{
		remove(it);
	}

	melds.push_back(meld);
}

void PlayerHand::readyHand()
{
	assert(isClosedHand());
	assert(ready_type == ReadyType::not_ready);

	ready_type = ReadyType::ready_hand;
}

void PlayerHand::doubleReady()
{
	assert(isClosedHand());
	assert(ready_type == ReadyType::not_ready);

	ready_type = ReadyType::double_ready;
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
	auto bonus_tile_count = 0;

	for (auto it : tiles)
	{
		bonus_tile_count += state.bonusTileCount(it);
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

PlayerHand::FreeTiles PlayerHand::makeFreeTiles() const
{
	if (melds.empty())
	{
		return FreeTiles(tiles.begin(), tiles.end());
	}

	return {};
}

bool PlayerHand::isReadyHand() const
{
	return ready_type == ReadyType::ready_hand;
}

bool PlayerHand::isDoubleReady() const
{
	return ready_type == ReadyType::double_ready;
}
}
