#include "player-hand.h"
#include <cassert>

void PlayerHand::tsumo(Tile tile)
{
	draw(tile);
}

void PlayerHand::ron(Tile tile)
{
	draw(tile);
	is_ron = true;
}

void PlayerHand::draw(Tile tile)
{
	assert(tiles.count(tile) < 4);

	tiles.insert(tile);
	last = tile;
}

void PlayerHand::discard(Tile tile)
{
	auto it = tiles.find(tile);
	assert(it != tiles.end());

	tiles.erase(it);
}

void PlayerHand::pon(Tile tile)
{
	assert(2 <= tiles.count(tile));

	draw(tile);
	is_claim = true;
}

void PlayerHand::kon(Tile tile)
{
	draw(tile);
	is_claim = true;
}

void PlayerHand::chii(Tile tile)
{
	draw(tile);
	is_claim = true;
}

Tile PlayerHand::lastTile() const
{
	return last;
}

bool PlayerHand::isRon() const
{
	return is_ron;
}

int PlayerHand::countTile(Tile tile) const
{
	return tiles.count(tile);
}

bool PlayerHand::isClaim() const
{
	return is_claim;
}

void PlayerHand::each(std::function<void(Tile)> fn) const
{
	for (auto it : tiles)
	{
		fn(it);
	}
}
