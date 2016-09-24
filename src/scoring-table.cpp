#include "scoring-table.h"
#include <cmath>
#include <cassert>

using namespace std;

int ScoringTable::dealerWinByDiscard(int han, int fu) const
{
	return roundUp(6 * basicPoints(han, fu));
}

int ScoringTable::dealerSelfDrawn(int han, int fu) const
{
	return roundUp(2 * basicPoints(han, fu));
}

int ScoringTable::nonDealerWinByDiscard(int han, int fu) const
{
	return roundUp(4 * basicPoints(han, fu));
}

std::pair<int, int> ScoringTable::nonDealerSelfDrawn(int han, int fu) const
{
	auto basic = basicPoints(han, fu);
	return make_pair(roundUp(basic), roundUp(2 * basic));
}

int ScoringTable::basicPoints(int han, int fu) const
{
	assert(0 < han);
	assert(0 < fu || 5 <= han);

	if (isMangan(han, fu)) return 2000;
	if (isHaneman(han)) return 3000;
	if (isBaiman(han)) return 4000;
	if (isSanbaiman(han)) return 6000;
	if (isYakuman(han)) return 8000;

	return static_cast<int>(fu * pow(2, 2 + han));
}

int ScoringTable::roundUp(int basic) const
{
	return static_cast<int>(std::ceil(basic / 100.0) * 100);
}

bool ScoringTable::isMangan(int han, int fu) const
{
	if (3 == han && 70 <= fu) return true;
	if (4 == han && 40 <= fu) return true;
	if (5 == han) return true;

	return false;
}

bool ScoringTable::isHaneman(int han) const
{
	return 6 <= han && han <= 7;
}

bool ScoringTable::isBaiman(int han) const
{
	return 8 <= han && han <= 10;
}

bool ScoringTable::isSanbaiman(int han) const
{
	return 11 <= han && han <= 12;
}

bool ScoringTable::isYakuman(int han) const
{
	return 13 <= han;
}
