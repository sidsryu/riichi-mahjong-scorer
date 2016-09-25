#include "terminal-or-honor-recognizer.h"
#include "pattern-define.h"
#include "pair.h"
#include "meld.h"

using namespace std;

void TerminalOrHonorRecognizer::reset()
{
	is_all_simples = true;
	is_terminal_or_honor_in_each_set = true;
	is_terminal_in_each_set = true;
	is_all_terminal_or_honor = true;
}

void TerminalOrHonorRecognizer::check(const Pair& pair)
{
	if (pair.isSimples())
	{
		is_terminal_or_honor_in_each_set = false;
		is_terminal_in_each_set = false;
		is_all_terminal_or_honor = false;
	}
	else
	{
		is_all_simples = false;

		if (pair.isHonors())
		{
			is_terminal_in_each_set = false;
		}
	}
}

void TerminalOrHonorRecognizer::check(const Meld& meld)
{
	if (meld.isSimples())
	{
		is_terminal_or_honor_in_each_set = false;
		is_terminal_in_each_set = false;
		is_all_terminal_or_honor = false;
	}
	else
	{
		is_all_simples = false;

		if (meld.isHonors())
		{
			is_terminal_in_each_set = false;
		}
		else if (!meld.isTerminals())
		{
			is_all_terminal_or_honor = false;
		}
	}
}

set<Pattern> TerminalOrHonorRecognizer::recognize()
{
	set<Pattern> patterns;

	if (is_all_simples)
	{
		patterns.insert(Pattern::AllSimples);
	}

	if (is_all_terminal_or_honor && is_terminal_in_each_set)
	{
		// all_terminals
	}
	else
	{
		if (is_all_terminal_or_honor)
		{
			patterns.insert(Pattern::AllTerminalsAndHornors);
		}
		else if (is_terminal_in_each_set)
		{
			patterns.insert(Pattern::TerminalInEachSet);
		}
		else if (is_terminal_or_honor_in_each_set)
		{
			patterns.insert(Pattern::TerminalOrHonorInEachSet);
		}
	}

	return patterns;
}
