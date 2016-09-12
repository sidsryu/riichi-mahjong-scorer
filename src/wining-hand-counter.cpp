#include "wining-hand-counter.h"
#include "player-hand.h"
#include "hand-define.h"
#include "wining-state.h"
#include "tile-holder.h"
#include "type-define.h"
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
			if (m.tiles[0] != m.tiles[1])
			{
				chii_count++;

				if (m.tiles[0] == hand.lastTile() || m.tiles[2] == hand.lastTile())
				{
					is_wait_multi = true;
				}
			}
		}
		if (chii_count == 4 && is_wait_multi)
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
	auto pair = holder.popNextPair();
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
