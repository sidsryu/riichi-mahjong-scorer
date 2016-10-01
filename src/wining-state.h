#pragma once

#include <set>

namespace mahjong {
enum class Tile;

struct WinByDiscardSituation
{
	bool is_one_shot { false };
	bool is_last_discard { false };
	bool is_robbing_quad { false };
};

struct SelfDrawnSituation
{
	bool is_one_shot { false };
	bool is_dead_wall { false };
	bool is_last_wall { false };
	bool is_uninterrupted_first_drawn { false };
};

class WiningState
{
public:
	WiningState();

	void winByDiscard(WinByDiscardSituation situation = {});
	void selfDrawn(SelfDrawnSituation situation = {});
	void setRoundWind(Tile tile);
	void setSeatWind(Tile tile);
	void addBonusTile(Tile tile);

	bool isWinByDiscard() const;
	bool isSelfDrawn() const;
	Tile roundWind() const;
	Tile seatWind() const;
	bool isOneShot() const;
	bool isLastDiscard() const;
	bool isLastTileFromTheWall() const;
	bool isDeadWallDraw() const;
	bool isRobbinQuad() const;
	int bonusTileCount(Tile tile) const;
	bool isUninterruptedFirstDrawn() const;
	bool isDealer() const;

private:
	bool is_win_by_discard { false };
	Tile round_wind;
	Tile seat_wind;
	bool is_one_shot { false };
	bool is_last_discard { false };
	bool is_robbing_quad { false };
	bool is_last_tile_from_the_wall { false };
	bool is_dead_wall_draw { false };
	std::multiset<Tile> bonus_tiles;
	bool is_uninterrupted_first_drawn { false };
};
}
