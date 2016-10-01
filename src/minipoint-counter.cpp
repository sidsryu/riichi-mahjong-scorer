#include "minipoint-counter.h"
#include "wining-state.h"
#include "tile-functor.h"
#include "wining-hand.h"
#include "player-hand.h"
#include "pair.h"
#include "meld.h"
#include <algorithm>

namespace mahjong {
MinipointCounter::MinipointCounter(const WiningHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

int MinipointCounter::total(bool is_round_up)
{
	if (isNoPointsHandSelfDrawn()) return 20;
	if (isSevenPairs()) return 25;

	point = 20;

	computeWining();
	computeMelds();
	computePair();
	computeWait();
	computeOpenNoPointsHand();

	return is_round_up ? roundUp(point) : point;
}

int MinipointCounter::roundUp(int point) const
{
	return static_cast<int>(std::ceil(point / 10.0) * 10);
}

bool MinipointCounter::isNoPointsHandSelfDrawn() const
{
	if (state.isWinByDiscard()) return false;

	auto is_multi_wait = false;
	for (auto it : hand.melds)
	{
		if (it.isOpen()) return false;
		if (it.isTripletOrQuad()) return false;

		is_multi_wait = it.isMultiWait(hand.last_tile);
	}

	return is_multi_wait;
}

bool MinipointCounter::isSevenPairs() const
{
	return 7 == hand.pairs.size();
}

void MinipointCounter::computeMelds()
{
	for (auto it : hand.melds)
	{
		if (it.isTripletOrQuad())
		{
			auto basic = 2;

			if (it.isHonors() || it.isTerminals())
			{
				basic *= 2;
			}

			if (!it.isOpen())
			{
				basic *= 2;
			}

			if (it.isQuad())
			{
				basic *= 4;
			}

			point += basic;
		}
	}
}

void MinipointCounter::computePair()
{
	for (auto it : hand.pairs)
	{
		if (it.isDragons())
		{
			point += 2;
		}
		else
		{
			if (it.isContain(state.seatWind()))
			{
				point += 2;
			}

			if (it.isContain(state.roundWind()))
			{
				point += 2;
			}
		}
	}
}

void MinipointCounter::computeWait()
{
	for (auto it : hand.pairs)
	{
		// pair wait
		if (it.isContain(hand.last_tile))
		{
			point += 2;
			return;
		}
	}

	for (auto it : hand.melds)
	{
		if (it.isOpen()) continue;
		if (it.isTripletOrQuad()) continue;

		if (it.isClosedWait(hand.last_tile))
		{
			point += 2;
			return;
		}

		if (it.isEdgeWait(hand.last_tile))
		{
			point += 2;
			return;
		}
	}
}

void MinipointCounter::computeWining()
{
	if (state.isSelfDrawn())
	{
		point += 2;
	}
	else
	{
		// closed win by discard
		for (auto it : hand.melds)
		{
			if (it.isOpen()) return;
		}
		point += 10;
	}
}

void MinipointCounter::computeOpenNoPointsHand()
{
	if (point == 20)
	{
		point += 10;
	}
}
}
