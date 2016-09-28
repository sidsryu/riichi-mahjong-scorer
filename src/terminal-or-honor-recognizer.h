#pragma once

#include "pattern-recognizer.h"

class TerminalOrHonorRecognizer: public PatternRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(TerminalOrHonorRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	int set_count { 0 };
	int simple_set_count { 0 };
	int honors_set_count { 0 };
	int terminals_set_count { 0 };
	int contained_terminal_set_count { 0 };
};
