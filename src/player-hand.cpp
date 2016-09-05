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
	assert(!is_riichi);
	assert(!is_double_riichi);

	draw(tile);
	is_claim = true;
}

void PlayerHand::kon(Tile tile)
{
	assert(!is_riichi);
	assert(!is_double_riichi);

	draw(tile);
	is_claim = true;
}

void PlayerHand::chii(Tile tile)
{
	assert(!is_riichi);
	assert(!is_double_riichi);

	draw(tile);
	is_claim = true;
}

void PlayerHand::riichi()
{
	assert(!is_claim);
	assert(!is_double_riichi);

	is_riichi = true;
}

void PlayerHand::doubleRiichi()
{
	assert(!is_claim);
	assert(!is_riichi);

	is_double_riichi = true;
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

bool PlayerHand::isRiichi() const
{
	return is_riichi;
}

bool PlayerHand::isDoubleRiichi() const
{
	return is_double_riichi;
}

void PlayerHand::each(std::function<void(Tile)> fn) const
{
	for (auto it : tiles)
	{
		fn(it);
	}
}
