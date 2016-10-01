#include "straight-recognizer.h"
#include "pattern-define.h"
#include "meld.h"

namespace mahjong {
void StraightRecognizer::reset()
{
	has_front_tile_of_sequences = {};
}

void StraightRecognizer::check(const Pair& pair)
{}

void StraightRecognizer::check(const Meld& meld)
{
	if (meld.isSequence())
	{
		auto code = static_cast<int>(meld.frontTile());
		auto suit = code / 100;
		auto number = code / 10 % 10;

		has_front_tile_of_sequences[number - 1][suit - 1] = true;
	}
}

std::set<Pattern> StraightRecognizer::recognize()
{
	for (const auto& it : has_front_tile_of_sequences)
	{
		if (it[0] && it[1] && it[2])
		{
			return { Pattern::ThreeColourStraights };
		}
	}

	for (auto i = 0; i < 3; i++)
	{
		// check tiles 1, 4 and 7 each suit
		// 123 456 789 xxx
		if (has_front_tile_of_sequences[0][i] &&
			has_front_tile_of_sequences[3][i] &&
			has_front_tile_of_sequences[6][i])
		{
			return { Pattern::Straight };
		}
	}

	return {};
}
}
