#include "wining-hand-counter.h"
#include "player-hand.h"
#include "pattern-define.h"
#include "wining-state.h"
#include "tile-holder.h"
#include "wining-hand.h"
#include "tile-functor.h"
#include "tile-define.h"
#include "pair.h"
#include "meld.h"
#include "hand-computer.h"
#include <array>
#include <cassert>

using namespace std;

WiningHandCounter::WiningHandCounter(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

void WiningHandCounter::compute()
{
	wining_hands.clear();
	patterns.clear();

	auto tile_holder = hand.makeHandHolder();

	WiningHand seed_hand;
	bt(seed_hand, tile_holder);


	HandComputer computer(state, wining_hands);
	computer.compute();

	computer.each([this](auto pattern) {
		patterns.insert(pattern);
	});
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

	if (holder.isNextTileTripletOrQuad())
	{
		tripletOrQuadBt(hand, holder);
	}

	if (holder.isNextTileSequence())
	{
		sequenceBt(hand, holder);
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
		if (it.isSame(pair))
		{
			return;
		}
	}
	hand.pairs.push_back(pair);

	bt(hand, holder);
}

void WiningHandCounter::tripletOrQuadBt(WiningHand hand, TileHolder holder)
{
	auto meld = holder.popNextTripletOrQuad();
	hand.melds.push_back(meld);

	bt(hand, holder);
}

void WiningHandCounter::sequenceBt(WiningHand hand, TileHolder holder)
{
	auto meld = holder.popNextSequence();
	hand.melds.push_back(meld);

	bt(hand, holder);
}

void WiningHandCounter::addWiningHand(WiningHand hand)
{
	wining_hands.push_back(hand);
}

bool WiningHandCounter::hasPattern(Pattern hand) const
{
	auto it = patterns.find(hand);
	return it != patterns.end();
}

bool WiningHandCounter::isPattenEmpty() const
{
	return 0 == patterns.size();
}
