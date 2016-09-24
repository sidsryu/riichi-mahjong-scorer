#pragma once

#include "hand-recognizer.h"

class NoPointsHandRecognizer: public HandRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(NoPointsHandRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:	
	int sequence_count { 0 };	
	bool has_value_pair { false };
	bool is_multi_wait { false };
};
