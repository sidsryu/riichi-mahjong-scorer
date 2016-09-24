#include "wining-state.h"
#include "tile-define.h"
#include <cassert>

WiningState::WiningState()
	: round_wind(Tile::EastWind)
	, own_wind(Tile::EastWind)	
{}

void WiningState::setClaim()
{
	is_claim = true;
}

void WiningState::setRiichi()
{
	assert(!is_double_riichi);
	is_riichi = true;
}

void WiningState::setDoubleRiichi()
{
	assert(!is_riichi);
	is_double_riichi = true;
}

void WiningState::setRon(Tile tile)
{
	is_ron = true;
	last_tile = tile;
}

void WiningState::setTsumo(Tile tile)
{
	is_ron = false;
	last_tile = tile;
}

void WiningState::setRountWind(Tile tile)
{
	round_wind = tile;
}

void WiningState::setOwnWind(Tile tile)
{
	own_wind = tile;
}

bool WiningState::isClaim() const
{
	return is_claim;
}

bool WiningState::isRiichi() const
{
	return is_riichi;
}

bool WiningState::isDoubleRiichi() const
{
	return is_double_riichi;
}

bool WiningState::isRon() const
{
	return is_ron;
}

bool WiningState::isTsumo() const
{
	return !is_ron;
}

Tile WiningState::roundWind() const
{
	return round_wind;
}

Tile WiningState::ownWind() const
{
	return own_wind;
}

Tile WiningState::lastTile() const
{
	return last_tile;
}
