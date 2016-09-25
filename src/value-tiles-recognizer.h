#pragma once

#include <set>
#include "hand-recognizer.h"

enum class Tile;

class ValueTilesRecognizer: public HandRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(ValueTilesRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	std::set<Tile> value_tiles;
};
