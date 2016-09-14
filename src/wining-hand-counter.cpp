#include "wining-hand-counter.h"
#include "player-hand.h"
#include "hand-define.h"
#include "wining-state.h"
#include "tile-holder.h"
#include "type-define.h"
#include "tile-functor.h"
#include <cassert>

WiningHandCounter::WiningHandCounter(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

void WiningHandCounter::calculate()
{
	auto tile_holder = hand.makeHandHolder();

	WiningHand wining_hand;
	wining_hand.last_tile = hand.lastTile();

	bt(wining_hand, tile_holder);
	assert(wining_hands.size() < 2);

	for (auto it : wining_hands)
	{		
		if (state.isDoubleRiichi())
		{
			hands.insert(Hand::DoubleReady);
		}

		if (state.isRiichi())
		{
			hands.insert(Hand::ReadyHand);
		}

		if (!hand.isClaim() && !state.isRon())
		{
			hands.insert(Hand::SelfPick);
		}

		auto chii_count = 0;
		auto is_wait_multi = false;
		for (auto m : it.melds)
		{
			if (!IsSame()(m.tiles[0], m.tiles[1]))
			{
				chii_count++;

				if ((IsSame()(m.tiles[0], it.last_tile) && !IsTerminal()(m.tiles[2])) ||
					(IsSame()(m.tiles[2], it.last_tile) && !IsTerminal()(m.tiles[0])))
				{
					is_wait_multi = true;
				}
			}
		}

		auto is_fu_pair = false;		
		if (IsDragon()(it.pairs.front().tiles.front()) ||
			IsSame()(it.pairs.front().tiles.front(), state.ownWind()) ||
			IsSame()(it.pairs.front().tiles.front(), state.roundWind()))
		{
			is_fu_pair = true;
		}

		if (chii_count == 4 && is_wait_multi && !is_fu_pair)
		{
			hands.insert(Hand::NoPointsHand);
		}

		if (7 == it.pairs.size())
		{
			hands.insert(Hand::SevenPairs);
		}

		if (!hand.isClaim())
		{
			for (size_t i = 0; i < it.melds.size(); i++)
			{
				if (IsSame()(it.melds[i].tiles[0], it.melds[i].tiles[1])) continue;

				for (auto j = i + 1; j < it.melds.size(); j++)
				{
					if (IsSame()(it.melds[j].tiles[0], it.melds[j].tiles[1])) continue;

					if (IsSame()(it.melds[i].tiles[0], it.melds[j].tiles[0]))
					{
						hands.insert(Hand::OneSetOfIdenticalSequences);
					}
				}
			}
		}
	}
}

void WiningHandCounter::bt(WiningHand hand, TileHolder holder)
{
	if (holder.empty())
	{
		addWiningHand(hand);
		return;
	}

	if (holder.isNextTilePair())
	{
		pairBt(hand, holder);
	}

	if (holder.isNextTilePonOrKan())
	{
		ponBt(hand, holder);
	}

	if (holder.isNextTileChii())
	{
		chiiBt(hand, holder);
	}
}

void WiningHandCounter::pairBt(WiningHand hand, TileHolder holder)
{
	if (1 <= hand.pairs.size() && 1 <= hand.melds.size())
	{
		return;
	}

	auto pair = holder.popNextPair();
	for (auto it : hand.pairs)
	{
		if (IsSame()(it.tiles.front(), pair.tiles.front()))
		{
			return;
		}
	}
	hand.pairs.push_back(pair);

	bt(hand, holder);
}

void WiningHandCounter::ponBt(WiningHand hand, TileHolder holder)
{
	auto meld = holder.popNextPonOrKan();
	hand.melds.push_back(meld);

	bt(hand, holder);
}

void WiningHandCounter::chiiBt(WiningHand hand, TileHolder holder)
{
	auto meld = holder.popNextChii();	
	hand.melds.push_back(meld);

	bt(hand, holder);
}

void WiningHandCounter::addWiningHand(WiningHand hand)
{
	wining_hands.push_back(hand);
}

bool WiningHandCounter::hasHand(Hand hand) const
{
	auto it = hands.find(hand);
	return it != hands.end();
}

bool WiningHandCounter::isNoHand() const
{
	return 0 == hands.size();
}
