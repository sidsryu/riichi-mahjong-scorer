#include "minipoint-counter.h"
#include "wining-hand-counter.h"
#include "hand-define.h"

MinipointCounter::MinipointCounter(const WiningHandCounter& hands)
	: hands(hands)
{}

int MinipointCounter::total() const
{
	if (hands.hasHand(Hand::SevenPairs)) return 25;
	if (hands.hasHand(Hand::NoPointsHand))
	{
		return hands.hasHand(Hand::SelfPick) ? 20 : 30;
	}

	return 20;
}
