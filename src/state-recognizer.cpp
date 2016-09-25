#include "state-recognizer.h"
#include "wining-state.h"
#include "pattern-define.h"

using namespace std;

void StateRecognizer::reset()
{}

void StateRecognizer::check(const Pair& pair)
{}

void StateRecognizer::check(const Meld& meld)
{}

set<Pattern> StateRecognizer::recognize()
{
	set<Pattern> patterns;

	if (state.isDoubleReady())
	{
		patterns.insert(Pattern::DoubleReady);
	}

	if (state.isReady())
	{
		patterns.insert(Pattern::ReadyHand);
	}

	if (state.isClosedHand() && state.isSelfDrawn())
	{
		patterns.insert(Pattern::SelfDrawn);
	}

	return patterns;
}
