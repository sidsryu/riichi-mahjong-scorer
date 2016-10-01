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
#include <map>

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

void PatternComputer::compute(WiningPatterns& out_patterns, WiningHand& out_wining_hand)
{
	highest_patterns.clear();

	WiningHandCollator c;
	for (const auto& h : c.collate(hand))
	{
		resetRecognizer();

		check(h);

		const auto& patterns = recognize();
		setHighest(h, patterns);
	}

	special(hand);

	out_patterns = highest_patterns;
	out_wining_hand = highest_wining_hand;
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

PatternComputer::WiningPatterns PatternComputer::recognize()
{
	set<Pattern> patterns;

	for (auto& it : recognizers)
	{
		auto p = it->recognize();
		patterns.insert(p.begin(), p.end());
	}

	return patterns;
}

void PatternComputer::special(const PlayerHand& hand)
{
	map<Tile, int> unique_tiles;
	for (auto it : hand.makeFreeTiles())
	{
		if (IsSimple()(it)) continue;
		unique_tiles[it]++;
	}

	if (13 == unique_tiles.size())
	{
		highest_patterns = { Pattern::ThirteenOrphans };

		WiningHand wining_hand;
		wining_hand.last_tile = hand.lastTile();
		for (auto it : unique_tiles)
		{
			if (2 == it.second)
			{
				auto p = Pair({ it.first, it.first });
				wining_hand.pairs.push_back(p);
			}
			else
			{
				wining_hand.tiles.push_back(it.first);
			}
		}
		highest_wining_hand = wining_hand;
	}
}

void PatternComputer::setHighest(const WiningHand& hand, const WiningPatterns& patterns)
{
	// limit hands can combine only themselves.
	WiningPatterns final_patterns;
	for (auto it : patterns)
	{
		if (IsLimitHand()(it))
		{
			final_patterns.insert(it);
		}
	}
	if (final_patterns.empty())
	{
		final_patterns = patterns;
	}

	// choose highest
	if (highest_patterns.empty())
	{
		highest_patterns = final_patterns;
		highest_wining_hand = hand;
	}
	else if ((int)*highest_patterns.rbegin() < (int)*final_patterns.rbegin())
	{
		highest_patterns = final_patterns;
		highest_wining_hand = hand;
	}
}
