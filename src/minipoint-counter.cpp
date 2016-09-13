#include "minipoint-counter.h"
#include "type-define.h"
#include "wining-state.h"
#include "tile-functor.h"

MinipointCounter::MinipointCounter(const WiningHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

int MinipointCounter::total() const
{
	auto is_closed = true;
	for (auto it : hand.melds)
	{
		if (it.is_open)
		{
			is_closed = false;
			break;
		}
	}

	auto is_no_points_hand = false;
	if (is_closed)
	{
		auto chii_count = 0;
		auto is_multi_wait = false;

		for (auto it : hand.melds)
		{
			if (!IsSame()(it.tiles[0], it.tiles[1]))
			{
				chii_count++;

				if ((IsSame()(it.tiles[0], hand.last_tile) && !IsTerminal()(it.tiles[2])) ||
					(IsSame()(it.tiles[2], hand.last_tile) && !IsTerminal()(it.tiles[0])))
				{
					is_multi_wait = true;
				}
			}
		}
		if (4 == chii_count && is_multi_wait)
		{
			is_no_points_hand = true;
		}
	}

	auto total = 20;
	if (is_closed && state.isRon())
	{
		total += 10;
	}

	if (is_no_points_hand)
	{
		return total;
	}

	if (!is_no_points_hand && state.isTsumo())
	{
		total += 2;
	}

	bool is_single_wait = false;
	for (auto it : hand.pairs)
	{
		if (IsSame()(it.tiles[0], hand.last_tile))
		{
			is_single_wait = true;
			break;
		}		
	}
	for (auto it : hand.melds)
	{
		if (!it.is_open)
		{
			if (IsSame()(it.tiles[1], hand.last_tile))
			{
				is_single_wait = true;
			}
			if (IsSame()(it.tiles[0], hand.last_tile) && IsTerminal()(it.tiles[2]) ||
				IsSame()(it.tiles[2], hand.last_tile) && IsTerminal()(it.tiles[0]))
			{
				is_single_wait = true;
			}
		}
	}
	if (is_single_wait)
	{
		total += 2;
	}

	return total;
}
