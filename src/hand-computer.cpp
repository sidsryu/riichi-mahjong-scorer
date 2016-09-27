#include "hand-computer.h"
#include "doubling-factor-counter.h"
#include "wining-hand.h"
#include "player-hand.h"
#include "hand-recognizer.h"
#include "pair.h"
#include "meld.h"
#include "state-recognizer.h"
#include "seven-pairs-recognizer.h"
#include "no-points-hand-recognizer.h"
#include "identical-sequences-recognizer.h"
#include "value-tiles-recognizer.h"
#include "straight-recognizer.h"
#include "triplets-or-quads-recognizer.h"
#include "three-colour-triplets-recognizer.h"
#include "terminal-or-honor-recognizer.h"
#include "dragons-recognizer.h"
#include "flush-recognizer.h"
#include "wining-hand-collator.h"

using namespace std;

HandComputer::HandComputer(const WiningState& state)
	: state(state)
{
	recognizers.emplace_back(make_unique<StateRecognizer>(state));
	recognizers.emplace_back(make_unique<SevenPairsRecognizer>(state));
	recognizers.emplace_back(make_unique<NoPointsHandRecognizer>(state));
	recognizers.emplace_back(make_unique<IdenticalSequencesRecognizer>(state));
	recognizers.emplace_back(make_unique<ValueTilesRecognizer>(state));
	recognizers.emplace_back(make_unique<StraightRecognizer>(state));
	recognizers.emplace_back(make_unique<TripletsOrQuadsRecognizer>(state));
	recognizers.emplace_back(make_unique<ThreeColourTripletsRecognizer>(state));
	recognizers.emplace_back(make_unique<TerminalOrHonorRecognizer>(state));
	recognizers.emplace_back(make_unique<DragonsRecognizer>(state));
	recognizers.emplace_back(make_unique<FlushRecognizer>(state));
}

HandComputer::~HandComputer() = default;

set<Pattern> HandComputer::compute(const PlayerHand& hand)
{
	highest_patterns.clear();

	WiningHandCollator c;
	for (const auto& h : c.collate(hand))
	{
		resetRecognizer();

		check(h);
		recognize();
	}

	return highest_patterns;
}

void HandComputer::resetRecognizer()
{
	for (auto& it : recognizers)
	{
		it->reset();
	}
}

void HandComputer::check(const WiningHand& hand)
{
	for (const auto& it : hand.pairs)
	{
		check(it);
	}

	for (const auto& it : hand.melds)
	{
		check(it);
	}
}

void HandComputer::check(const Pair& pair)
{
	for (auto& it : recognizers)
	{
		it->check(pair);
	}
}

void HandComputer::check(const Meld& meld)
{
	for (auto& it : recognizers)
	{
		it->check(meld);
	}
}

void HandComputer::recognize()
{
	set<Pattern> patterns;

	for (auto& it : recognizers)
	{
		auto p = it->recognize();
		patterns.insert(p.begin(), p.end());
	}
	if (patterns.empty()) return;


	if (highest_patterns.empty())
	{
		highest_patterns = patterns;
	}
	else if ((int)*highest_patterns.rbegin() < (int)*patterns.rbegin())
	{
		highest_patterns = patterns;
	}
}
