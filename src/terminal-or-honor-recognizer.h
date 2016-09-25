#pragma once

#include "hand-recognizer.h"

class TerminalOrHonorRecognizer: public HandRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(TerminalOrHonorRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	bool is_all_simples { true };
	bool is_terminal_or_honor_in_each_set { true };
	bool is_terminal_in_each_set { true };
	bool is_all_terminal_or_honor { true };
};
