#pragma once

#include "hand-recognizer.h"
#include <array>

enum class Tile;

class StraightRecognizer: public HandRecognizer
{
	using SuitFlag = std::array<bool, 3>;
	using NumberFlag = std::array<SuitFlag, 9>;

public:
	RECOGNIZER_CONSTRUCTOR(StraightRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	NumberFlag has_front_tile_of_sequences {};
};
