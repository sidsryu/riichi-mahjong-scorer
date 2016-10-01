#include "flush-recognizer.h"
#include "pattern-define.h"
#include "pair.h"
#include "meld.h"
#include "player-hand.h"
#include "wining-state.h"

namespace mahjong {
void FlushRecognizer::reset()
{
	has_honors = false;
	has_suit_tiles = {};
	number_count = {};
}

void FlushRecognizer::check(const Pair& pair)
{
	if (pair.isHonors())
	{
		has_honors = true;
	}
	else
	{
		auto code = static_cast<int>(pair.frontTile());
		auto suit = code / 100;
		auto number = code / 10 % 10;

		has_suit_tiles[suit - 1] = true;;
		number_count[number - 1] += 2;
	}
}

void FlushRecognizer::check(const Meld& meld)
{
	if (meld.isHonors())
	{
		has_honors = true;
	}
	else
	{
		auto code = static_cast<int>(meld.frontTile());
		auto suit = code / 100;
		auto number = code / 10 % 10;

		has_suit_tiles[suit - 1] = true;

		if (meld.isSequence())
		{
			number_count[number - 1 + 0]++;
			number_count[number - 1 + 1]++;
			number_count[number - 1 + 2]++;
		}
		else
		{
			number_count[number - 1] += 3;
			if (meld.isQuad()) number_count[number - 1]++;
		}
	}
}

std::set<Pattern> FlushRecognizer::recognize()
{
	auto suit_count = 0;
	for (auto it : has_suit_tiles)
	{
		if (it)
		{
			suit_count++;
		}
	}

	if (suit_count == 1)
	{
		if (has_honors)
		{
			return { Pattern::HalfFlush };
		}
		else
		{
			if (hand.isClosedHand())
			{
				bool is_nine_gates = true;
				if (number_count.front() < 3) is_nine_gates = false;
				if (number_count.back() < 3) is_nine_gates = false;
				for (auto it : number_count)
				{
					if (it == 0) is_nine_gates = false;
				}

				if (is_nine_gates)
				{
					return { Pattern::NineGates };
				}
			}

			return { Pattern::Flush };
		}
	}

	return {};
}
}
