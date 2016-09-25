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

void WiningState::ready()
{
	assert(!is_double_ready);
	is_ready = true;
}

void WiningState::doubleReady()
{
	assert(!is_ready);
	is_double_ready = true;
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

bool WiningState::isReady() const
{
	return is_ready;
}

bool WiningState::isDoubleReady() const
{
	return is_double_ready;
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
