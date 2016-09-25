#pragma once

#include "hand-recognizer.h"

class DragonsRecognizer: public HandRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(DragonsRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	int dragon_count { 0 };	
	bool is_dragon_pair { false };
};
