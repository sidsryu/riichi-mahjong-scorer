#pragma once

#include "pattern-recognizer.h"

namespace mahjong {
class TripletsOrQuadsRecognizer: public PatternRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(TripletsOrQuadsRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	int quad_count { 0 };
	int triplet_count { 0 };
	int closed_triplet_or_quad_count { 0 };
	int closed_count_modifier { 0 };
};
}
