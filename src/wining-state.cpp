#include "wining-state.h"
#include "tile-define.h"
#include <cassert>

WiningState::WiningState()
	: round_wind(Tile::EastWind)
	, seat_wind(Tile::EastWind)	
{}

void WiningState::claim()
{
	is_claim = true;
}

void WiningState::riichi()
{
	assert(!is_double_riichi);
	is_riichi = true;
}

void WiningState::doubleRiichi()
{
	assert(!is_riichi);
	is_double_riichi = true;
}

void WiningState::winByDiscard(Tile tile)
{
	is_win_by_discard = true;
	last_tile = tile;
}

void WiningState::selfDrawn(Tile tile)
{
	is_win_by_discard = false;
	last_tile = tile;
}

void WiningState::setRountWind(Tile tile)
{
	round_wind = tile;
}

void WiningState::setSeatWind(Tile tile)
{
	seat_wind = tile;
}

bool WiningState::isClosedHand() const
{
	return !is_claim;
}

bool WiningState::isRiichi() const
{
	return is_riichi;
}

bool WiningState::isDoubleRiichi() const
{
	return is_double_riichi;
}

bool WiningState::isWinByDiscard() const
{
	return is_win_by_discard;
}

bool WiningState::isSelfDrawn() const
{
	return !is_win_by_discard;
}

Tile WiningState::roundWind() const
{
	return round_wind;
}

Tile WiningState::seatWind() const
{
	return seat_wind;
}

Tile WiningState::lastTile() const
{
	return last_tile;
}
