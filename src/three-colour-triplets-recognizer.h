#pragma once

#include "pattern-recognizer.h"
#include <array>

class ThreeColourTripletsRecognizer: public PatternRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(ThreeColourTripletsRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	std::array<int, 9> front_tile_count_of_triplets_or_quads {};
};
