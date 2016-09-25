#include "three-colour-triplets-recognizer.h"
#include "pattern-define.h"
#include "meld.h"

void ThreeColourTripletsRecognizer::reset()
{
	front_tile_count_of_triplets_or_quads = {};
}

void ThreeColourTripletsRecognizer::check(const Pair& pair)
{}

void ThreeColourTripletsRecognizer::check(const Meld& meld)
{
	if (meld.isTripletOrQuad())
	{
		auto code = static_cast<int>(meld.frontTile());
		auto number = code / 10 % 10;

		front_tile_count_of_triplets_or_quads[number-1]++;
	}
}

std::set<Pattern> ThreeColourTripletsRecognizer::recognize()
{
	for (auto it : front_tile_count_of_triplets_or_quads)
	{
		if (it == 3)
		{
			return { Pattern::ThreeColourTriplets };
		}
	}

	return {};
}
