#pragma once

#include <utility>
namespace mahjong {
class ScoringTable
{
public:
	int dealerWinByDiscard(int doubling_factor, int minipoints) const;
	int dealerSelfDrawn(int doubling_factor, int minipoints) const;
	int nonDealerWinByDiscard(int doubling_factor, int minipoints) const;
	std::pair<int, int> nonDealerSelfDrawn(int doubling_factor, int minipoints) const;

private:
	int basicPoints(int doubling_factor, int minipoints) const;
	int roundUp(int basic) const;
	bool isMangan(int doubling_factor, int minipoints) const;
	bool isHaneman(int doubling_factor) const;
	bool isBaiman(int doubling_factor) const;
	bool isSanbaiman(int doubling_factor) const;
	bool isYakuman(int doubling_factor) const;
};
}
