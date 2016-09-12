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
	TileHolder holder;
	hand.each([&holder](Tile tile) {
		holder.add(tile);
	});

	WiningHand wining_hand;
	bt(wining_hand, holder);

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

				if ((IsSame()(m.tiles[0], hand.lastTile()) && !IsTerminal()(m.tiles[2])) ||
					(IsSame()(m.tiles[2], hand.lastTile()) && !IsTerminal()(m.tiles[0])))
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

	if (holder.isNextTilePon())
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
	if (1 < hand.melds.size() && 1 < hand.pairs.size())
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
	auto meld = holder.popNextPon();
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
