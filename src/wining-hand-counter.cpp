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
#include "wining-hand-collator.h"
#include "hand-computer.h"
#include "doubling-factor-report.h"
#include <array>
#include <cassert>

using namespace std;

WiningHandCounter::WiningHandCounter(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

DoublingFactorReport WiningHandCounter::compute()
{
	DoublingFactorReport report;

	WiningHandCollator collator(hand);
	auto wining_hands = collator.collate();

	HandComputer computer(state, wining_hands);
	report.patterns = computer.compute();

	report.bonus_tile_count = hand.bonusTileCount(state);
	report.doubling_factor = 0;

	patterns = report.patterns;

	return report;
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
