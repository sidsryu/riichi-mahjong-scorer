#pragma once

class WiningState
{
public:
	void setRiichi();
	void setDoubleRiichi();
	void setRon();
	void setTsumo();

	bool isRiichi() const;
	bool isDoubleRiichi() const;
	bool isRon() const;
	bool isTsumo() const;	

private:
	bool is_riichi { false };
	bool is_double_riichi { false };
	bool is_ron { false };
	bool is_tsumo { false };
};
