#pragma once

#include <utility>

class ScoringTable
{
public:
	int dealerRon(int han, int fu) const;
	int dealerTsumo(int han, int fu) const;
	int nonDealerRon(int han, int fu) const;
	std::pair<int, int> nonDealerTsumo(int han, int fu) const;

private:
	int basicPoints(int han, int fu) const;
	int roundUp(int basic) const;
	bool isMangan(int han, int fu) const;
	bool isHaneman(int han) const;
	bool isBaiman(int han) const;
	bool isSanbaiman(int han) const;
	bool isYakuman(int han) const;
};
