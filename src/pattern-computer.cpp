#include "pattern-computer.h"
#include "doubling-factor-counter.h"
#include "wining-hand.h"
#include "player-hand.h"
#include "pattern-recognizer.h"
#include "pair.h"
#include "meld.h"
#include "tile-functor.h"
#include "pattern-functor.h"
#include "pattern-define.h"
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
#include "winds-recognizer.h"
#include "all-green-recognizer.h"

using namespace std;

PatternComputer::PatternComputer(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{
	recognizers.emplace_back(make_unique<StateRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<SevenPairsRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<NoPointsPatternRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<IdenticalSequencesRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<ValueTilesRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<StraightRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<TripletsOrQuadsRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<ThreeColourTripletsRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<TerminalOrHonorRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<DragonsRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<FlushRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<WindsRecognizer>(hand, state));
	recognizers.emplace_back(make_unique<AllGreenRecognizer>(hand, state));
}

PatternComputer::~PatternComputer() = default;

set<Pattern> PatternComputer::compute()
{
	highest_patterns.clear();

	WiningHandCollator c;
	for (const auto& h : c.collate(hand))
	{
		resetRecognizer();

		check(h);
		recognize();
	}
		
	special(hand);

	return highest_patterns;
}

void PatternComputer::resetRecognizer()
{
	for (auto& it : recognizers)
	{
		it->reset();
	}
}

void PatternComputer::check(const WiningHand& hand)
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

void PatternComputer::check(const Pair& pair)
{
	for (auto& it : recognizers)
	{
		it->check(pair);
	}
}

void PatternComputer::check(const Meld& meld)
{
	for (auto& it : recognizers)
	{
		it->check(meld);
	}
}

void PatternComputer::recognize()
{
	// compute patterns
	set<Pattern> patterns;
	for (auto& it : recognizers)
	{
		auto p = it->recognize();
		patterns.insert(p.begin(), p.end());
	}
	if (patterns.empty()) return;

	// limit hands can combine only themselves.
	set<Pattern> limit_hands;
	for (auto it : patterns)
	{
		if (IsLimitHand()(it))
		{
			limit_hands.insert(it);
		}
	}
	if (!limit_hands.empty())
	{
		patterns = limit_hands;
	}

	// choose highest
	if (highest_patterns.empty())
	{
		highest_patterns = patterns;
	}
	else if ((int)*highest_patterns.rbegin() < (int)*patterns.rbegin())
	{
		highest_patterns = patterns;
	}
}

void PatternComputer::special(const PlayerHand& hand)
{
	set<Tile> tiles;
	for (auto it : hand.makeFreeTiles())
	{
		if (IsSimple()(it)) continue;
		tiles.insert(it);
	}

	if (13 == tiles.size())
	{
		highest_patterns = { Pattern::ThirteenOrphans };
	}
}
