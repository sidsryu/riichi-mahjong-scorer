#pragma once

#include <vector>

enum class Tile;

class PlayerHand
{
public:
	void tsumo(Tile tile);
	void ron(Tile tile);

private:
	std::vector<Tile> tiles;
};
