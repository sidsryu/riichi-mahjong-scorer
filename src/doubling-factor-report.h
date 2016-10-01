#pragma once

#include "wining-hand.h"
#include <set>

enum class Pattern;
struct WiningHand;

struct DoublingFactorReport
{
	WiningHand wining_hand;
	std::set<Pattern> patterns;
	int bonus_tile_count { 0 };
	int doubling_factor { 0 };
};
