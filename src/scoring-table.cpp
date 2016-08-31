#include "scoring-table.h"
#include <cmath>
#include <cassert>

using namespace std;

int ScoringTable::dealerRon(int han, int fu) const
{
	return roundUp(6 * basicPoints(han, fu));
}

int ScoringTable::dealerTsumo(int han, int fu) const
{
	return roundUp(2 * basicPoints(han, fu));
}

int ScoringTable::nonDealerRon(int han, int fu) const
{
	return roundUp(4 * basicPoints(han, fu));
}

std::pair<int, int> ScoringTable::nonDealerTsumo(int han, int fu) const
{
	auto basic = basicPoints(han, fu);
	return make_pair(roundUp(basic), roundUp(2 * basic));
}

int ScoringTable::basicPoints(int han, int fu) const
{
	assert(0 < han);
	assert(0 < fu);

	return static_cast<int>(fu * pow(2, 2+han));
}

int ScoringTable::roundUp(int basic) const
{
	return static_cast<int>(std::ceil(basic / 100.0) * 100);
}
