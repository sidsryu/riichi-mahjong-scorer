#pragma once

enum class Tile;

class WiningState
{
public:
	WiningState();

	void riichi();
	void doubleRiichi();
	void claim();
	void winByDiscard(Tile tile);
	void selfDrawn(Tile tile);
	void setRountWind(Tile tile);
	void setSeatWind(Tile tile);

	bool isRiichi() const;
	bool isDoubleRiichi() const;
	bool isClosedHand() const;
	bool isWinByDiscard() const;
	bool isSelfDrawn() const;
	Tile roundWind() const;
	Tile seatWind() const;
	Tile lastTile() const;

private:
	bool is_riichi { false };
	bool is_double_riichi { false };
	bool is_claim { false };
	bool is_win_by_discard { false };
	Tile round_wind;
	Tile seat_wind;
	Tile last_tile;
};
