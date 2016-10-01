#pragma once

#include "pattern-recognizer.h"

namespace mahjong {
class StateRecognizer: public PatternRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(StateRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;
};
}
