#pragma once

enum class Tile;

class WiningState
{
public:
	WiningState();

	void setRiichi();
	void setDoubleRiichi();
	void setRon();
	void setTsumo();	
	void setRountWind(Tile tile);
	void setOwnWind(Tile tile);
	
	bool isRiichi() const;
	bool isDoubleRiichi() const;
	bool isRon() const;
	bool isTsumo() const;	
	Tile roundWind() const;
	Tile ownWind() const;

private:
	bool is_riichi { false };
	bool is_double_riichi { false };
	bool is_ron { false };
	bool is_tsumo { false };
	Tile round_wind;
	Tile own_wind;
};
