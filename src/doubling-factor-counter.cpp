#include "doubling-factor-counter.h"
#include "player-hand.h"
#include "wining-state.h"
#include "doubling-factor-report.h"
#include "pattern-define.h"
#include "pattern-computer.h"
#include "doubling-factor-table.h"
#include "pair.h"
#include "meld.h"

using namespace std;

DoubligFactorCounter::DoubligFactorCounter(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

DoublingFactorReport DoubligFactorCounter::report()
{
	DoublingFactorReport r;
	
	PatternComputer c(hand, state);
	c.compute(r.patterns, r.wining_hand);

	r.bonus_tile_count = hand.bonusTileCount(state);

	DoublingFactorTable t(hand, state);
	r.doubling_factor = t.total(r.patterns);
	r.doubling_factor += r.bonus_tile_count;

	return r;
}
