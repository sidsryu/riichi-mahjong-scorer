#include "doubling-factor-counter.h"
#include "player-hand.h"
#include "wining-state.h"
#include "doubling-factor-report.h"
#include "pattern-define.h"
#include "hand-computer.h"

using namespace std;

DoubligFactorCounter::DoubligFactorCounter(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

DoublingFactorReport DoubligFactorCounter::report()
{
	DoublingFactorReport r;

	HandComputer c(state);
	r.patterns = c.compute(hand);

	r.bonus_tile_count = hand.bonusTileCount(state);
	r.doubling_factor = 0;

	return r;
}
