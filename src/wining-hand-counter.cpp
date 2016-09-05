#include "wining-hand-counter.h"
#include "player-hand.h"
#include "hand-define.h"
#include "wining-hand.h"
#include "tile-holder.h"

WiningHandCounter::WiningHandCounter(const PlayerHand& hand)
	: hand(hand)
{}

void WiningHandCounter::calculate()
{
	TileHolder holder;
	hand.each([&holder](Tile tile) {
		holder.add(tile);
	});

	WiningHand wining_hand;
	bt(wining_hand, holder);

	for (auto it : wining_hands)
	{
		if (!hand.isClaim() && !hand.isRon())
		{
			hands.insert(Hand::SelfPick);
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
	Meld meld;
	meld.tiles = holder.popNextPair();
	hand.melds.push_back(meld);

	bt(hand, holder);
}

void WiningHandCounter::ponBt(WiningHand hand, TileHolder holder)
{
	Meld meld;
	meld.tiles = holder.popNextPon();
	hand.melds.push_back(meld);

	bt(hand, holder);
}

void WiningHandCounter::chiiBt(WiningHand hand, TileHolder holder)
{
	Meld meld;
	meld.tiles = holder.popNextChii();	
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
