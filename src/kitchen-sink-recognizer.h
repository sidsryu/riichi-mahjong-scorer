#pragma once

#include "hand-recognizer.h"
#include "wining-hand.h"

class KitchenSinkRecognizer: public HandRecognizer
{
public:
	KitchenSinkRecognizer(const WiningState& state);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	WiningHand wining_hand;
};
