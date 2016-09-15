#pragma once

enum class Tile;

struct IsSame
{
	bool operator()(const Tile& lhv, const Tile& rhv) const;
};

struct IsSimple
{
	bool operator()(const Tile& tile) const;
};

struct IsTerminal
{
	bool operator()(const Tile& tile) const;
};

struct IsDragon
{
	bool operator()(const Tile& tile) const;
};

struct IsHornor
{
	bool operator()(const Tile& tile) const;
};

struct NextTile
{
	Tile operator()(const Tile& tile) const;
};
