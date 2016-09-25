#pragma once

#include <vector>

class Pair;
class Meld;

struct WiningHand
{
	std::vector<Pair> pairs;
	std::vector<Meld> melds;
};
