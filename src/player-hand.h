#pragma once

#include <set>
#include <functional>

enum class Tile;

class PlayerHand
{
public:
	void tsumo(Tile tile);
	void ron(Tile tile);
	void discard(Tile tile);
	void pon(Tile tile);
	void kon(Tile tile);
	void chii(Tile tile);
	void riichi();
	void doubleRiichi();

	Tile lastTile() const;
	bool isRon() const;
	int countTile(Tile tile) const;
	bool isClaim() const;
	bool isRiichi() const;
	bool isDoubleRiichi() const;

	void each(std::function<void(Tile)> fn) const;

private:
	void draw(Tile tile);

private:
	std::multiset<Tile> tiles;
	Tile last;
	bool is_ron { false };
	bool is_claim { false };
	bool is_riichi { false };
	bool is_double_riichi { false };
};
