#include "meld.h"
#include "tile-functor.h"
#include "wining-state.h"
#include <cassert>

namespace mahjong {
Meld::Meld()
{}

Meld::Meld(std::vector<Tile> tiles, bool is_open)
	: tiles(tiles)
	, is_open(is_open)
{
	assert(
		// sequence
		(3 == tiles.size() &&
			IsSimple()(tiles[1]) &&
			IsSame()(NextTile()(tiles[0]), tiles[1]) &&
			IsSame()(NextTile()(tiles[1]), tiles[2])) ||
		// triplet
			(3 == tiles.size() &&
				IsSame()(tiles[0], tiles[1]) &&
				IsSame()(tiles[0], tiles[2])) ||
		// quad
				(4 == tiles.size() &&
					IsSame()(tiles[0], tiles[1]) &&
					IsSame()(tiles[0], tiles[2]) &&
					IsSame()(tiles[0], tiles[3]))
	);
}

bool Meld::isOpen() const
{
	return is_open;
}

bool Meld::isSequence() const
{
	return !IsSame()(tiles.front(), tiles.back());
}

bool Meld::isTriplet() const
{
	return 3 == tiles.size() && IsSame()(tiles.front(), tiles.back());
}

bool Meld::isQuad() const
{
	return 4 == tiles.size() && IsSame()(tiles.front(), tiles.back());
}

bool Meld::isTripletOrQuad() const
{
	// same 'isTriplet() || isQuad()'
	return !isSequence();
}

bool Meld::isContain(Tile tile) const
{
	for (auto it : tiles)
	{
		if (IsSame()(it, tile)) return true;
	}

	return false;
}

bool Meld::isMultiWait(Tile last_tile) const
{
	if (is_open) return false;
	if (isTripletOrQuad()) return false;

	if (IsSame()(tiles.front(), last_tile))
	{
		return !IsTerminal()(tiles.back());
	}

	if (IsSame()(tiles.back(), last_tile))
	{
		return !IsTerminal()(tiles.front());
	}

	return false;
}

bool Meld::isClosedWait(Tile last_tile) const
{
	if (is_open) return false;
	if (isTripletOrQuad()) return false;

	return IsSame()(tiles[1], last_tile);
}

bool Meld::isEdgeWait(Tile last_tile) const
{
	if (is_open) return false;
	if (isTripletOrQuad()) return false;

	return (IsTerminal()(tiles.front()) && IsSame()(tiles.back(), last_tile)) ||
		(IsTerminal()(tiles.back()) && IsSame()(tiles.front(), last_tile));
}

bool Meld::isSame(const Meld& meld) const
{
	return IsSame()(tiles.front(), meld.tiles.front()) &&
		IsSame()(tiles.back(), meld.tiles.back());
}

bool Meld::isSimples() const
{
	return IsSimple()(tiles.front()) && IsSimple()(tiles.back());
}

bool Meld::isHonors() const
{
	return IsHonor()(tiles.front());
}

bool Meld::isDragons() const
{
	return IsDragon()(tiles.front());
}

bool Meld::isWinds() const
{
	return IsWind()(tiles.front());
}

bool Meld::isTerminals() const
{
	return IsTerminal()(tiles.front()) && IsTerminal()(tiles.back());
}

bool Meld::hasTerminal() const
{
	return IsTerminal()(tiles.front()) || IsTerminal()(tiles.back());
}

bool Meld::isValueTiles(const WiningState& state) const
{
	if (IsDragon()(tiles.front())) return true;
	if (IsSame()(tiles.front(), state.roundWind())) return true;
	if (IsSame()(tiles.front(), state.seatWind())) return true;

	return false;
}

int Meld::bonusTileCount(const WiningState& state) const
{
	auto bonus_tile_count = 0;

	for (auto it : tiles)
	{
		bonus_tile_count += state.bonusTileCount(it);
	}

	return bonus_tile_count;
}

Tile Meld::frontTile() const
{
	return tiles.front();
}

bool Meld::isValid() const
{
	return !tiles.empty();
}

bool Meld::isGreens() const
{
	for (auto it : tiles)
	{
		if (!IsGreen()(it)) return false;
	}

	return true;
}
}
