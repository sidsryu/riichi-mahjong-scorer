#pragma once

#include "pattern-recognizer.h"
#include <array>

class FlushRecognizer: public PatternRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(FlushRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	bool has_honors { false };
	std::array<bool, 3> has_suit_tiles {};
};
