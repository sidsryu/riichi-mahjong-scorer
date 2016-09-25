#pragma once

enum class Tile;

class WiningState
{
public:
	WiningState();

	void readyHand();
	void doubleReady();
	void claim();
	void winByDiscard(Tile tile);
	void selfDrawn(Tile tile);
	void setRountWind(Tile tile);
	void setSeatWind(Tile tile);
	void setOneShot();
	void setLastDiscard();
	void setLastTileFromTheWall();
	void setDeadWallDraw();
	void setRobbingQuad();

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
	bool is_last_tile_from_the_wall { false };
	bool is_dead_wall_draw { false };
	bool is_robbing_quad { false };
};
