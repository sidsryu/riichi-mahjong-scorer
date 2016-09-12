#include "player-hand.h"
#include "tile-functor.h"
#include "type-define.h"
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

void PlayerHand::bindPon(BindTiles tiles)
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

void PlayerHand::bindKan(BindTiles tiles)
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

void PlayerHand::bindCloseKan(BindTiles tiles)
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

void PlayerHand::bindChii(BindTiles tiles)
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

bool PlayerHand::isClaim() const
{
	for (auto it : melds)
	{
		if (it.is_open) return true;
	}

	return false;
}

Tile PlayerHand::lastTile() const
{
	return last_tile;
}

void PlayerHand::each(std::function<void(Tile)> fn) const
{
	for (auto it : tiles)
	{
		fn(it);
	}
}
