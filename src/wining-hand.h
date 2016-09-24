#pragma once

#include <vector>
#include <set>

enum class Tile;
enum class Pattern;
class Pair;
class Meld;
class WiningState;

struct WiningHand
{
	std::vector<Pair> pairs;
	std::vector<Meld> melds;
	Tile last_tile;

	std::set<Pattern> patterns;
};
