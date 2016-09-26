#pragma once

#include <set>

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
};

class WiningState
{
public:
	WiningState();

	void readyHand();
	void doubleReady();
	void claim();
	void winByDiscard(Tile tile, WinByDiscardSituation situation = {});
	void selfDrawn(Tile tile, SelfDrawnSituation situation = {});
	void setRountWind(Tile tile);
	void setSeatWind(Tile tile);
	void addBonusTile(Tile tile);

	bool isReadyHand() const;
	bool isDoubleReady() const;
	bool isClosedHand() const;
	bool isWinByDiscard() const;
	bool isSelfDrawn() const;
	Tile roundWind() const;
	Tile seatWind() const;
	Tile lastTile() const;
	bool isOneShot() const;
	bool isLastDiscard() const;
	bool isLastTileFromTheWall() const;
	bool isDeadWallDraw() const;
	bool isRobbinQuad() const;
	bool isBonusTile(Tile tile) const;

private:
	bool is_ready_hand { false };
	bool is_double_ready { false };
	bool is_claim { false };
	bool is_win_by_discard { false };
	Tile round_wind;
	Tile seat_wind;
	Tile last_tile;
	bool is_one_shot { false };
	bool is_last_discard { false };
	bool is_robbing_quad { false };
	bool is_last_tile_from_the_wall { false };
	bool is_dead_wall_draw { false };
	std::set<Tile> bonus_tiles;
};
