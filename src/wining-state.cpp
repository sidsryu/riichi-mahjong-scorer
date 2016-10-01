#include "wining-state.h"
#include "tile-define.h"
#include "tile-functor.h"
#include <cassert>

namespace mahjong {
WiningState::WiningState()
	: round_wind(Tile::EastWind)
	, seat_wind(Tile::EastWind)
{}

void WiningState::winByDiscard(WinByDiscardSituation situation)
{
	is_win_by_discard = true;

	is_one_shot = situation.is_one_shot;
	is_last_discard = situation.is_last_discard;
	is_robbing_quad = situation.is_robbing_quad;
	assert(
		!(is_last_discard && is_robbing_quad) &&
		!(is_last_discard && is_one_shot)
	);
}

void WiningState::selfDrawn(SelfDrawnSituation situation)
{
	is_win_by_discard = false;

	is_one_shot = situation.is_one_shot;
	is_last_tile_from_the_wall = situation.is_last_wall;
	is_dead_wall_draw = situation.is_dead_wall;
	is_uninterrupted_first_drawn = situation.is_uninterrupted_first_drawn;

	assert(
		!(is_uninterrupted_first_drawn && is_one_shot) &&
		!(is_uninterrupted_first_drawn && is_last_tile_from_the_wall) &&
		!(is_uninterrupted_first_drawn && is_dead_wall_draw) &&
		!(is_last_tile_from_the_wall && is_dead_wall_draw)
	);
}

void WiningState::setRoundWind(Tile tile)
{
	round_wind = tile;
}

void WiningState::setSeatWind(Tile tile)
{
	seat_wind = tile;
}

void WiningState::addBonusTile(Tile tile)
{
	assert(bonus_tiles.size() < 10);
	assert(bonus_tiles.count(tile) < 4);

	bonus_tiles.insert(tile);
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

bool WiningState::isOneShot() const
{
	return is_one_shot;
}

bool WiningState::isLastDiscard() const
{
	return is_last_discard;
}

bool WiningState::isLastTileFromTheWall() const
{
	return is_last_tile_from_the_wall;
}

bool WiningState::isDeadWallDraw() const
{
	return is_dead_wall_draw;
}

bool WiningState::isRobbinQuad() const
{
	return is_robbing_quad;
}

int WiningState::bonusTileCount(Tile tile) const
{
	auto bonus_tile_count { 0 };

	if (IsRedFive()(tile))
	{
		bonus_tile_count++;
	}

	for (auto it : bonus_tiles)
	{
		if (IsSame()(it, tile))
		{
			bonus_tile_count++;
		}
	}

	return bonus_tile_count;
}

bool WiningState::isUninterruptedFirstDrawn() const
{
	return is_uninterrupted_first_drawn;
}

bool WiningState::isDealer() const
{
	return IsSame()(seat_wind, Tile::EastWind);
}
}
