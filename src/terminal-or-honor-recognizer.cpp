#include "terminal-or-honor-recognizer.h"
#include "pattern-define.h"
#include "pair.h"
#include "meld.h"

using namespace std;

namespace mahjong {
void TerminalOrHonorRecognizer::reset()
{
	set_count = 0;
	simple_set_count = 0;
	honors_set_count = 0;
	terminals_set_count = 0;
	contained_terminal_set_count = 0;
}

void TerminalOrHonorRecognizer::check(const Pair& pair)
{
	set_count++;

	if (pair.isSimples())
	{
		simple_set_count++;
	}

	if (pair.isHonors())
	{
		honors_set_count++;
	}

	if (pair.isTerminals())
	{
		terminals_set_count++;
		contained_terminal_set_count++;
	}
}

void TerminalOrHonorRecognizer::check(const Meld& meld)
{
	set_count++;

	if (meld.isSimples())
	{
		simple_set_count++;
	}

	if (meld.isHonors())
	{
		honors_set_count++;
	}

	if (meld.hasTerminal())
	{
		contained_terminal_set_count++;

		if (meld.isTerminals())
		{
			terminals_set_count++;
		}
	}
}

set<Pattern> TerminalOrHonorRecognizer::recognize()
{
	set<Pattern> patterns;

	if (simple_set_count == set_count)
	{
		patterns.insert(Pattern::AllSimples);
	}

	if (honors_set_count == set_count)
	{
		patterns.insert(Pattern::AllHonors);
	}

	if (terminals_set_count == set_count)
	{
		patterns.insert(Pattern::AllTerminals);
	}

	if (honors_set_count + terminals_set_count == set_count)
	{
		patterns.insert(Pattern::AllTerminalsAndHornors);
	}
	else
	{
		if (contained_terminal_set_count == set_count)
		{
			patterns.insert(Pattern::TerminalInEachSet);
		}
		else if (contained_terminal_set_count + honors_set_count == set_count)
		{
			patterns.insert(Pattern::TerminalOrHonorInEachSet);
		}
	}

	return patterns;
}
}
