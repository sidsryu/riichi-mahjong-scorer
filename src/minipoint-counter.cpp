#include "minipoint-counter.h"
#include "type-define.h"
#include "wining-state.h"
#include "tile-functor.h"

MinipointCounter::MinipointCounter(const WiningHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

int MinipointCounter::total(bool is_round_up)
{
	if (isNoPointsHandSelfPick()) return 20;
	if (isSevenPairs()) return 25;

	point = 20;

	calculateWining();
	calculateMelds();
	calculatePair();
	calculateWait();
	calculateOpenNoPointsHand();

	return is_round_up ? roundUp(point) : point;
}

int MinipointCounter::roundUp(int point) const
{
	return static_cast<int>(std::ceil(point / 10.0) * 10);
}

bool MinipointCounter::isNoPointsHandSelfPick() const
{
	if (state.isRon()) return false;

	auto is_multi_wait = false;
	for (auto it : hand.melds)
	{
		if (it.is_open) return false;
		if (IsSame()(it.tiles[0], it.tiles[1])) return false;

		if ((IsSame()(it.tiles[0], hand.last_tile) && !IsTerminal()(it.tiles[2])) ||
			(IsSame()(it.tiles[2], hand.last_tile) && !IsTerminal()(it.tiles[0])))
		{
			is_multi_wait = true;
		}
	}

	return is_multi_wait;
}

bool MinipointCounter::isSevenPairs() const
{
	return 7 == hand.pairs.size();
}

void MinipointCounter::calculateMelds()
{
	for (auto it : hand.melds)
	{
		if (IsSame()(it.tiles[0], it.tiles[1]))
		{
			auto basic = 2;

			if (IsHornor()(it.tiles[0]) || IsTerminal()(it.tiles[0]))
			{
				basic *= 2;
			}

			if (!it.is_open)
			{
				basic *= 2;
			}

			if (4 == it.tiles.size())
			{
				basic *= 4;
			}

			point += basic;
		}
	}
}

void MinipointCounter::calculatePair()
{
	for (auto it : hand.pairs)
	{
		auto tile = it.tiles.front();

		if (IsDragon()(tile))
		{
			point += 2;
		}
		else
		{
			if (IsSame()(tile, state.ownWind()))
			{
				point += 2;
			}

			if (IsSame()(tile, state.roundWind()))
			{
				point += 2;
			}
		}
	}
}

void MinipointCounter::calculateWait()
{
	for (auto it : hand.pairs)
	{
		// pair wait
		if (IsSame()(it.tiles[0], hand.last_tile))
		{
			point += 2;
			return;
		}
	}

	for (auto it : hand.melds)
	{
		if (it.is_open) continue;
		if (IsSame()(it.tiles[0], it.tiles[1])) continue;

		// closed wait
		if (IsSame()(it.tiles[1], hand.last_tile))
		{
			point += 2;
			return;
		}

		// edge wait
		if (IsSame()(it.tiles[0], hand.last_tile) && IsTerminal()(it.tiles[2]) ||
			IsSame()(it.tiles[2], hand.last_tile) && IsTerminal()(it.tiles[0]))
		{
			point += 2;
			return;
		}
	}
}

void MinipointCounter::calculateWining()
{
	if (state.isTsumo())
	{
		point += 2;
	}
	else
	{
		// closed ron
		for (auto it : hand.melds)
		{
			if (it.is_open) return;
		}
		point += 10;
	}
}

void MinipointCounter::calculateOpenNoPointsHand()
{
	if (point == 20)
	{
		point += 10;
	}
}
