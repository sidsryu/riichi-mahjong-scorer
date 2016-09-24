#include "hand-computer.h"
#include "wining-hand-counter.h"
#include "wining-hand.h"
#include "player-hand.h"
#include "hand-recognizer.h"
#include "pair.h"
#include "meld.h"
#include "kitchen-sink-recognizer.h"

using namespace std;

HandComputer::HandComputer(const WiningState& state, const WiningHands& hands)
	: state(state)
	, hands(hands)
{
	recognizers.emplace_back(make_unique<KitchenSinkRecognizer>(state));
}

HandComputer::~HandComputer() = default;

void HandComputer::compute()
{
	for (const auto& h : hands)
	{
		resetRecognizer();

		check(h);
		recognize();
	}
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
	for (auto& it : recognizers)
	{
		auto patterns = it->recognize();
		if (patterns.empty()) continue;

		if (highest_patterns.empty())
		{
			highest_patterns = patterns;
		}
		else if ((int)*highest_patterns.rbegin() < (int)*patterns.rbegin())
		{
			highest_patterns = patterns;
		}
	}
}

void HandComputer::each(std::function<void(Pattern)> fn) const
{
	for (auto it : highest_patterns)
	{
		fn(it);
	}
}
