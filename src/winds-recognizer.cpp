#include "winds-recognizer.h"
#include "pattern-define.h"
#include "pair.h"
#include "meld.h"

namespace mahjong {
void WindsRecognizer::reset()
{
	wind_count = 0;
	is_wind_pair = false;
}

void WindsRecognizer::check(const Pair& pair)
{
	if (pair.isWinds())
	{
		is_wind_pair = true;
	}
}

void WindsRecognizer::check(const Meld& meld)
{
	if (meld.isWinds())
	{
		wind_count++;
	}
}

std::set<Pattern> WindsRecognizer::recognize()
{
	if (is_wind_pair && wind_count == 3)
	{
		return { Pattern::LittleFourWinds };
	}

	if (wind_count == 4)
	{
		return { Pattern::BigFourWinds };
	}

	return {};
}
}
