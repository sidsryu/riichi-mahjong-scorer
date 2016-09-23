#pragma once

#include <vector>

enum class Tile;
class WiningState;

class Pair
{
public:
	Pair(std::vector<Tile> tiles);

	bool isSimples() const;
	bool isHonors() const;
	bool isDragons() const;	
	bool isValuePair(const WiningState& state) const;
	bool isContain(Tile tile) const;
	Tile frontTile() const;
	bool isSame(const Pair& pair) const;

private:
	std::vector<Tile> tiles;
};
