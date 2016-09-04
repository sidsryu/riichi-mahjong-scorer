#include "wining-hand-counter.h"
#include "player-hand.h"
#include "hand-define.h"

WiningHandCounter::WiningHandCounter(const PlayerHand& hand)
	: hand(hand)
{}

void WiningHandCounter::calculate()
{
	hands.insert(Hand::SelfPick);

	hand.each([](Tile tile) {
	});
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
