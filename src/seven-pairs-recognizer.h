#pragma once

#include "hand-recognizer.h"
#include <vector>

enum class Tile;

class SevenPairsRecognizer: public HandRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(SevenPairsRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	std::vector<Tile> front_tiles_of_pair;
};
