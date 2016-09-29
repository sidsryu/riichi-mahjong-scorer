#include "pattern-functor.h"
#include "pattern-define.h"

bool IsLimitHand::operator()(const Pattern& pattern) const
{
	return Pattern::Flush < pattern;
}
