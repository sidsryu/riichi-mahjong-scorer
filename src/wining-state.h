#pragma once

enum class Tile;

class WiningState
{
public:
	WiningState();

	void setClaim();
	void setRiichi();
	void setDoubleRiichi();
	void setRon(Tile tile);
	void setTsumo(Tile tile);
	void setRountWind(Tile tile);
	void setOwnWind(Tile tile);
	
	bool isClaim() const;
	bool isRiichi() const;
	bool isDoubleRiichi() const;
	bool isRon() const;
	bool isTsumo() const;	
	Tile roundWind() const;
	Tile ownWind() const;
	Tile lastTile() const;

private:
	bool is_claim { false };
	bool is_riichi { false };
	bool is_double_riichi { false };
	bool is_ron { false };
	Tile round_wind;
	Tile own_wind;
	Tile last_tile;
};
