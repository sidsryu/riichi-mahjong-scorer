#include "pair.h"
#include "wining-state.h"
#include "tile-functor.h"
#include <cassert>

Pair::Pair(std::vector<Tile> tiles)
	: tiles(tiles)
{
	assert(2 == tiles.size() && IsSame()(tiles.front(), tiles.back()));
}

bool Pair::isSimples() const
{
	return IsSimple()(tiles.front());
}

bool Pair::isHonors() const
{
	return IsHonor()(tiles.front());
}

bool Pair::isDragons() const
{
	return IsDragon()(tiles.front());
}

bool Pair::isValuePair(const WiningState& state) const
{
	if (IsDragon()(tiles.front())) return true;
	if (IsSame()(tiles.front(), state.roundWind())) return true;
	if (IsSame()(tiles.front(), state.seatWind())) return true;

	return false;
}

bool Pair::isContain(Tile tile) const
{
	return IsSame()(tiles.front(), tile);
}

Tile Pair::frontTile() const
{
	return tiles.front();
}

bool Pair::isSame(const Pair& pair) const
{
	return IsSame()(tiles.front(), pair.tiles.front());
}
