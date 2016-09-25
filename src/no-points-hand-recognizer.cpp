#include "no-points-hand-recognizer.h"
#include "wining-state.h"
#include "pattern-define.h"
#include "pair.h"
#include "meld.h"

using namespace std;

void NoPointsHandRecognizer::reset()
{
	sequence_count = 0;
	has_value_pair = false;
	is_multi_wait = false;
}

void NoPointsHandRecognizer::check(const Pair& pair)
{
	if (pair.isValueTiles(state))
	{
		has_value_pair = true;
	}
}

void NoPointsHandRecognizer::check(const Meld& meld)
{
	if (meld.isSequence())
	{
		sequence_count++;

		auto last_tile = state.lastTile();
		if (meld.isMultiWait(last_tile))
		{
			is_multi_wait = true;
		}
	}
}

set<Pattern> NoPointsHandRecognizer::recognize()
{
	if (state.isClosedHand())
	{
		if (has_value_pair) return {};

		if (sequence_count == 4 && is_multi_wait)
		{
			return { Pattern::NoPointsHand };
		}
	}

	return {};
}
