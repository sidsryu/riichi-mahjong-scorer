#include "doubling-factor-counter.h"
#include "player-hand.h"
#include "wining-state.h"
#include "doubling-factor-report.h"
#include "pattern-define.h"
#include "pattern-computer.h"
#include "doubling-factor-table.h"

using namespace std;

DoubligFactorCounter::DoubligFactorCounter(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

DoublingFactorReport DoubligFactorCounter::report()
{
	PatternComputer c(hand, state);
	auto patterns = c.compute();
	auto bonus_tile_count = hand.bonusTileCount(state);

	DoublingFactorTable t(hand, state);
	auto doubling_factor = t.total(patterns) + bonus_tile_count;

	DoublingFactorReport r;
	r.patterns = patterns;
	r.bonus_tile_count = bonus_tile_count;
	r.doubling_factor = doubling_factor;

	return r;
}
