#pragma once

enum class Tile;

struct IsSame
{
	bool operator()(const Tile& lhv, const Tile& rhv) const;
};

struct NextTile
{
	Tile operator()(const Tile& tile) const;
};
