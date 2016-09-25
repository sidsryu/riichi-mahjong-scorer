#pragma once

#include <vector>

enum class Tile;
class WiningState;

class Meld
{
public:
	Meld(std::vector<Tile> tiles, bool is_open);

	bool isOpen() const;
	bool isSequence() const;
	bool isTriplet() const;
	bool isQuad() const;
	bool isTripletOrQuad() const;
	bool isContain(Tile tile) const;
	bool isMultiWait(Tile last_tile) const;
	bool isClosedWait(Tile last_tile) const;
	bool isEdgeWait(Tile last_tile) const;
	bool isSame(const Meld& meld) const;
	bool isSimples() const;	
	bool isHonors() const;	
	bool isDragons() const;
	bool isTerminals() const;
	bool hasTerminal() const;
	bool isValueTiles(const WiningState& state) const;
	Tile frontTile() const;

private:
	std::vector<Tile> tiles;
	bool is_open { false };
};
