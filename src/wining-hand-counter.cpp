#include "wining-hand-counter.h"

void WiningHandCounter::add(Hand hand)
{
	hands.insert(hand);
}

bool WiningHandCounter::hasHand(Hand hand) const
{
	auto it = hands.find(hand);
	return it != hands.end();
}
