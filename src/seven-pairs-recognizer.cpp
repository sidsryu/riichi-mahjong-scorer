#include "seven-pairs-recognizer.h"
#include "wining-state.h"
#include "pattern-define.h"
#include "tile-functor.h"
#include "pair.h"

using namespace std;

namespace mahjong {
void SevenPairsRecognizer::reset()
{
	front_tiles_of_pair.clear();
}

void SevenPairsRecognizer::check(const Pair& pair)
{
	auto tile = pair.frontTile();
	for (auto it : front_tiles_of_pair)
	{
		if (IsSame()(it, tile))
		{
			return;
		}
	}

	front_tiles_of_pair.push_back(tile);
}

void SevenPairsRecognizer::check(const Meld& meld)
{}

set<Pattern> SevenPairsRecognizer::recognize()
{
	if (7 == front_tiles_of_pair.size())
	{
		return { Pattern::SevenPairs };
	}

	return {};
}
}
