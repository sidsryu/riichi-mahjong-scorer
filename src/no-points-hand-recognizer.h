#pragma once

#include "pattern-recognizer.h"

namespace mahjong {
class NoPointsPatternRecognizer: public PatternRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(NoPointsPatternRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	int sequence_count { 0 };
	bool has_value_pair { false };
	bool is_multi_wait { false };
};
}
