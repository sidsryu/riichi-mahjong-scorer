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
	auto it = wining_hand;

	bool is_all_simple = true;
	for (auto m : it.pairs)
	{
		if (!m.isSimples())
		{
			is_all_simple = false;
		}
	}
	for (auto m : it.melds)
	{
		if (!m.isSimples())
		{
			is_all_simple = false;
		}
	}
	if (is_all_simple)
	{
		it.patterns.insert(Pattern::AllSimples);
	}

	auto is_terminal_or_honor_in_each_set = true;
	auto is_terminal_in_each_set = true;
	auto is_all_terminal_or_honor = true;
	for (auto m : it.pairs)
	{
		if (m.isSimples())
		{
			is_terminal_or_honor_in_each_set = false;
			is_terminal_in_each_set = false;
			is_all_terminal_or_honor = false;
		}
	}
	for (auto m : it.melds)
	{
		if (m.isTripletOrQuad())
		{
			if (m.isSimples())
			{
				is_terminal_or_honor_in_each_set = false;
				is_terminal_in_each_set = false;
				is_all_terminal_or_honor = false;
			}
			else if (m.isHonors())
			{
				is_terminal_in_each_set = false;
			}
		}
		else
		{
			is_all_terminal_or_honor = false;

			if (!m.hasTerminal())
			{
				is_terminal_or_honor_in_each_set = false;
				is_terminal_in_each_set = false;
			}
		}
	}
	if (is_terminal_or_honor_in_each_set)
	{
		it.patterns.insert(Pattern::TerminalOrHonorInEachSet);
	}
	if (is_terminal_in_each_set)
	{
		it.patterns.insert(Pattern::TerminalInEachSet);
	}
	if (is_all_terminal_or_honor)
	{
		it.patterns.insert(Pattern::AllTerminalsAndHornors);
	}

	auto dragon_count = 0;
	auto is_dragon_pair = false;
	for (auto m : it.pairs)
	{
		if (m.isDragons())
		{
			is_dragon_pair = true;
		}
	}
	for (auto m : it.melds)
	{
		if (m.isDragons())
		{
			dragon_count++;
		}
	}
	if (is_dragon_pair && dragon_count == 2)
	{
		it.patterns.insert(Pattern::LittleThreeDragons);
	}

	auto suit_number = 0;
	auto is_flush = true;
	auto is_honor = false;
	for (auto m : it.pairs)
	{
		if (m.isHonors())
		{
			is_honor = true;
		}
		else
		{
			auto suit = static_cast<int>(m.frontTile()) / 100;
			if (suit_number == 0) suit_number = suit;
			if (suit_number != suit)
			{
				is_flush = false;
			}
		}
	}
	for (auto m : it.melds)
	{
		if (m.isHonors())
		{
		}
		else
		{
			auto suit = static_cast<int>(m.frontTile()) / 100;
			if (suit_number == 0) suit_number = suit;
			if (suit_number != suit)
			{
				is_flush = false;
			}
		}
	}
	if (is_flush)
	{
		if (is_honor)
		{
			it.patterns.insert(Pattern::HalfFlush);
		}
		else
		{
			it.patterns.insert(Pattern::Flush);
		}
	}

	return it.patterns;
}
