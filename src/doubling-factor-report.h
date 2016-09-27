#pragma once

#include <set>

enum class Pattern;

struct DoublingFactorReport
{	
	std::set<Pattern> patterns;
	int bonus_tile_count { 0 };	
	int doubling_factor { 0 };
};
