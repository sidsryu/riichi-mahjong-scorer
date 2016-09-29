#pragma once

#include <vector>

enum class Tile;
class WiningState;

class Pair
{
public:
	Pair();
	Pair(std::vector<Tile> tiles);

	bool isSimples() const;
	bool isTerminals() const;
	bool isHonors() const;
	bool isDragons() const;	
	bool isWinds() const;
	bool isValueTiles(const WiningState& state) const;
	bool isContain(Tile tile) const;
	Tile frontTile() const;
	bool isSame(const Pair& pair) const;
	bool isValid() const;
	bool isGreens() const;

private:
	std::vector<Tile> tiles;
};
