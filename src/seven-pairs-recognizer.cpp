#include "seven-pairs-recognizer.h"
#include "wining-state.h"
#include "pattern-define.h"

using namespace std;

void SevenPairsRecognizer::reset()
{
	pair_count = 0;
}

void SevenPairsRecognizer::check(const Pair& pair)
{
	pair_count++;
}

void SevenPairsRecognizer::check(const Meld& meld)
{}

set<Pattern> SevenPairsRecognizer::recognize()
{
	set<Pattern> patterns;

	if (pair_count == 7)
	{
		patterns.insert(Pattern::SevenPairs);
	}

	return patterns;
}