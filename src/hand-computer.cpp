#include "hand-computer.h"
#include "wining-hand-counter.h"
#include "wining-hand.h"
#include "hand-recognizer.h"
#include "pair.h"
#include "meld.h"

HandComputer::HandComputer(const WiningHandCounter& counter, 
	const WiningState& state, const WiningHands& hands)
	: counter(counter)
	, state(state)
	, hands(hands)
{}

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
		it->recognize();
	}
}

void HandComputer::each(std::function<void(Pattern)> fn) const
{
	for (auto it : patterns)
	{
		fn(it);
	}
}
