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
	DoublingFactorReport r;

	HandComputer c(state);
	r.patterns = c.compute(hand);

	r.bonus_tile_count = hand.bonusTileCount(state);
	r.doubling_factor = 0;

	return r;
}
