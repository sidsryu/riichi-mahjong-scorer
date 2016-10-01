#include "identical-sequences-recognizer.h"
#include "wining-state.h"
#include "player-hand.h"
#include "pattern-define.h"
#include "meld.h"

using namespace std;

void IdenticalSequencesRecognizer::reset()
{
	identity_infos.clear();
}

void IdenticalSequencesRecognizer::check(const Pair& pair)
{}

void IdenticalSequencesRecognizer::check(const Meld& meld)
{
	if (meld.isTripletOrQuad()) return;

	for (auto& it : identity_infos)
	{
		if (it.first.isSame(meld))
		{
			it.second++;
			return;
		}
	}

	identity_infos.push_back({ meld, 1 });
}

std::set<Pattern> IdenticalSequencesRecognizer::recognize()
{
	if (hand.isClosedHand())
	{
		auto identical_set_count = 0;

		for (const auto& it : identity_infos)
		{
			// identity set count
			// 123 xxx xxx xxx : 0 sets
			// 123 123 xxx xxx : 1 set
			// 123 123 123 xxx : 1 set
			// 123 123 123 123 : 2 sets

			identical_set_count += it.second / 2;
		}

		if (identical_set_count == 2)
		{
			return { Pattern::TwoSetsOfIdenticalSequences };
		}

		if (identical_set_count == 1)
		{
			return { Pattern::OneSetOfIdenticalSequences };
		}
	}

	return {};
}
