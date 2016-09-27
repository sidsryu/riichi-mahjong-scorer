#include "scoring-table.h"
#include <cmath>
#include <cassert>

using namespace std;

int ScoringTable::dealerWinByDiscard(int doubling_factor, int minipoints) const
{
	return roundUp(6 * basicPoints(doubling_factor, minipoints));
}

int ScoringTable::dealerSelfDrawn(int doubling_factor, int minipoints) const
{
	return roundUp(2 * basicPoints(doubling_factor, minipoints));
}

int ScoringTable::nonDealerWinByDiscard(int doubling_factor, int minipoints) const
{
	return roundUp(4 * basicPoints(doubling_factor, minipoints));
}

std::pair<int, int> ScoringTable::nonDealerSelfDrawn(int doubling_factor, int minipoints) const
{
	auto basic = basicPoints(doubling_factor, minipoints);
	return make_pair(roundUp(basic), roundUp(2 * basic));
}

int ScoringTable::basicPoints(int doubling_factor, int minipoints) const
{
	assert(0 < doubling_factor);
	assert(0 < minipoints || 5 <= doubling_factor);

	if (isMangan(doubling_factor, minipoints)) return 2000;
	if (isHaneman(doubling_factor)) return 3000;
	if (isBaiman(doubling_factor)) return 4000;
	if (isSanbaiman(doubling_factor)) return 6000;
	if (isYakuman(doubling_factor)) return 8000;

	return static_cast<int>(minipoints * pow(2, 2 + doubling_factor));
}

int ScoringTable::roundUp(int basic) const
{
	return static_cast<int>(std::ceil(basic / 100.0) * 100);
}

bool ScoringTable::isMangan(int doubling_factor, int minipoints) const
{
	if (3 == doubling_factor && 70 <= minipoints) return true;
	if (4 == doubling_factor && 40 <= minipoints) return true;
	if (5 == doubling_factor) return true;

	return false;
}

bool ScoringTable::isHaneman(int doubling_factor) const
{
	return 6 <= doubling_factor && doubling_factor <= 7;
}

bool ScoringTable::isBaiman(int doubling_factor) const
{
	return 8 <= doubling_factor && doubling_factor <= 10;
}

bool ScoringTable::isSanbaiman(int doubling_factor) const
{
	return 11 <= doubling_factor && doubling_factor <= 12;
}

bool ScoringTable::isYakuman(int doubling_factor) const
{
	return 13 <= doubling_factor;
}
