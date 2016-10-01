#include "wining-hand-collator.h"
#include "wining-hand.h"
#include "pair.h"
#include "meld.h"
#include "player-hand.h"
#include "tile-holder.h"
#include <set>

using namespace std;

WiningHandCollator::WiningHands WiningHandCollator::collate(const PlayerHand& hand)
{
	wining_hands.clear();

	auto seed_holder = hand.makeHandHolder();
	auto seed_hand = WiningHand();
	seed_hand.last_tile = hand.lastTile();

	backtrack(seed_hand, seed_holder);

	return wining_hands;
}

void WiningHandCollator::backtrack(const WiningHand& extended_hand, const TileHolder& extended_holder)
{
	if (extended_holder.empty())
	{
		wining_hands.push_back(extended_hand);
		return;
	}

	backtrackPair(extended_hand, extended_holder);
	backtrackTripletOrQuad(extended_hand, extended_holder);
	backtrackSequence(extended_hand, extended_holder);
}

void WiningHandCollator::backtrackPair(WiningHand extended_hand, TileHolder extended_holder)
{
	auto pair = extended_holder.popPairWithFrontTile();
	if (pair.isValid() && 
		(0 == extended_hand.pairs.size() || 0 == extended_hand.melds.size()))
	{
		extended_hand.pairs.push_back(pair);
		backtrack(extended_hand, extended_holder);
	}
}

void WiningHandCollator::backtrackTripletOrQuad(WiningHand extended_hand, TileHolder extended_holder)
{
	auto meld = extended_holder.popTripletOrQuadWithFrontTile();
	if (meld.isValid() && extended_hand.pairs.size() < 2)
	{
		extended_hand.melds.push_back(meld);
		backtrack(extended_hand, extended_holder);
	}
}

void WiningHandCollator::backtrackSequence(WiningHand extended_hand, TileHolder extended_holder)
{
	auto meld = extended_holder.popSequenceWithFrontTile();
	if (meld.isValid() && extended_hand.pairs.size() < 2)
	{
		extended_hand.melds.push_back(meld);
		backtrack(extended_hand, extended_holder);
	}
}
