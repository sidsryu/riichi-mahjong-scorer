#include "all-green-recognizer.h"
#include "pattern-define.h"
#include "pair.h"
#include "meld.h"

void AllGreenRecognizer::reset()
{
	is_all_green = true;
}

void AllGreenRecognizer::check(const Pair& pair)
{
	if (!pair.isGreens())
	{
		is_all_green = false;
	}
}

void AllGreenRecognizer::check(const Meld& meld)
{
	if (!meld.isGreens())
	{
		is_all_green = false;
	}
}

std::set<Pattern> AllGreenRecognizer::recognize()
{
	if (is_all_green)
	{
		return { Pattern::AllGreen };
	}

	return {};
}
