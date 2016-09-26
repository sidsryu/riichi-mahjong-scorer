#pragma once

#include <set>

struct DoublingFactorReport
{	
	std::set<Pattern> patterns;
	int bonus_tile_count { 0 };	
	int doubling_factor { 0 };
};
