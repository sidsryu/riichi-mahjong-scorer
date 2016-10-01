#pragma once

#include "pattern-recognizer.h"

namespace mahjong {
class WindsRecognizer: public PatternRecognizer
{
public:
	RECOGNIZER_CONSTRUCTOR(WindsRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	int wind_count { 0 };
	bool is_wind_pair { false };
};
}
