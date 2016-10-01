#include "state-recognizer.h"
#include "wining-state.h"
#include "player-hand.h"
#include "pattern-define.h"

using namespace std;

namespace mahjong {
void StateRecognizer::reset()
{}

void StateRecognizer::check(const Pair& pair)
{}

void StateRecognizer::check(const Meld& meld)
{}

set<Pattern> StateRecognizer::recognize()
{
	set<Pattern> patterns;

	if (hand.isReadyHand() || hand.isDoubleReady())
	{
		if (hand.isReadyHand())
		{
			patterns.insert(Pattern::ReadyHand);
		}

		if (hand.isDoubleReady())
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

		if (state.isUninterruptedFirstDrawn())
		{
			if (state.isDealer())
			{
				patterns.insert(Pattern::HeavenlyHand);
			}
			else
			{
				patterns.insert(Pattern::EarthlyHand);
			}
		}
	}

	if (hand.isClosedHand() && state.isSelfDrawn())
	{
		patterns.insert(Pattern::SelfDrawn);
	}

	return patterns;
}
}
