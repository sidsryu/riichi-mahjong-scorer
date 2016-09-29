#pragma once

#include "pattern-recognizer.h"

class AllGreenRecognizer: public PatternRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(AllGreenRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	int is_all_green { true };
};
