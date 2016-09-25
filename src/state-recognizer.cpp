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

	if (state.isReadyHand() || state.isDoubleReady())
	{
		if (state.isReadyHand())
		{
			patterns.insert(Pattern::ReadyHand);
		}

		if (state.isDoubleReady())
		{
			patterns.insert(Pattern::DoubleReady);
		}

		if (state.isOneShot())
		{
			patterns.insert(Pattern::OneShot);
		}
	}

	if (state.isWinByDiscard())
	{
		if (state.isLastDiscard())
		{
			patterns.insert(Pattern::LastDiscard);
		}

		if (state.isRobbinQuad())
		{
			patterns.insert(Pattern::RobbingQuad);
		}
	}

	if (state.isSelfDrawn())
	{
		if (state.isLastTileFromTheWall())
		{
			patterns.insert(Pattern::LastTileFromTheWall);
		}

		if (state.isDeadWallDraw())
		{
			patterns.insert(Pattern::DeadWallDraw);
		}
	}

	if (state.isClosedHand() && state.isSelfDrawn())
	{
		patterns.insert(Pattern::SelfDrawn);
	}

	return patterns;
}
