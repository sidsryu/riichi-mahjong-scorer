#pragma once

#include <set>

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

	Tile lastTile() const;
	bool isRon() const;
	int countTile(Tile tile) const;
	bool isClaim() const;

private:
	void draw(Tile tile);

private:
	std::multiset<Tile> tiles;
	Tile last;
	bool is_ron { false };
	bool is_claim { false };
};
