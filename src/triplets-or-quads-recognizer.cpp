#include "triplets-or-quads-recognizer.h"
#include "pattern-define.h"
#include "wining-state.h"
#include "meld.h"

using namespace std;

void TripletsOrQuadsRecognizer::reset()
{
	quad_count = 0;
	triplet_count = 0;
	closed_triplet_or_quad_count = 0;
	closed_count_modifier = 0;
}

void TripletsOrQuadsRecognizer::check(const Pair& pair)
{}

void TripletsOrQuadsRecognizer::check(const Meld& meld)
{
	if (meld.isTripletOrQuad())
	{
		if (meld.isQuad())
		{
			quad_count++;
		}

		if (meld.isTriplet())
		{
			triplet_count++;
		}

		if (!meld.isOpen())
		{
			closed_triplet_or_quad_count++;
		}
	}

	if (state.isWinByDiscard())
	{
		if (!meld.isOpen() && meld.isContain(state.lastTile()))
		{
			if (meld.isSequence())
			{
				closed_count_modifier++;
			}
			else
			{
				closed_count_modifier--;
			}
		}
	}
}

set<Pattern> TripletsOrQuadsRecognizer::recognize()
{
	set<Pattern> patterns;

	// only count self drawn triplets and/or quads
	if (closed_count_modifier < 0)
	{
		closed_triplet_or_quad_count += closed_count_modifier;
	}

	if (quad_count == 3)
	{
		patterns.insert(Pattern::ThreeQuads);
	}

	if (quad_count == 4)
	{
		patterns.insert(Pattern::FourQuads);
	}
	
	if (closed_triplet_or_quad_count == 3)
	{
		patterns.insert(Pattern::ThreeClosedTriplets);
	}

	if (closed_triplet_or_quad_count == 4)
	{
		patterns.insert(Pattern::FourClosedTriplets);
	}

	if (triplet_count + quad_count == 4)
	{
		patterns.insert(Pattern::AllTriplets);
	}

	return patterns;
}
