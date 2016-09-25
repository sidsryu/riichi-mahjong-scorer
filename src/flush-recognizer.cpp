#include "flush-recognizer.h"
#include "pattern-define.h"
#include "pair.h"
#include "meld.h"

void FlushRecognizer::reset()
{
	has_honors = false;
	has_suit_tiles = {};
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

		has_suit_tiles[suit - 1] = true;;
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

		has_suit_tiles[suit - 1] = true;
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
			return { Pattern::Flush };
		}
	}

	return {};
}
