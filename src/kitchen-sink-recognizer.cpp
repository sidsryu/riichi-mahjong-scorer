#include "kitchen-sink-recognizer.h"
#include "wining-state.h"
#include "pattern-define.h"
#include "tile-define.h"
#include "tile-functor.h"
#include "player-hand.h"
#include "pair.h"
#include "meld.h"
#include <array>

using namespace std;

KitchenSinkRecognizer::KitchenSinkRecognizer(const WiningState& state)
	: HandRecognizer(state)
{}

void KitchenSinkRecognizer::reset()
{
	wining_hand = WiningHand();
}

void KitchenSinkRecognizer::check(const Pair& pair)
{
	wining_hand.pairs.push_back(pair);
}

void KitchenSinkRecognizer::check(const Meld& meld)
{
	wining_hand.melds.push_back(meld);
}

set<Pattern> KitchenSinkRecognizer::recognize()
{
	return {};
}
