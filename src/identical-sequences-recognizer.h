#pragma once

#include <vector>
#include "pattern-recognizer.h"

namespace mahjong {
class IdenticalSequencesRecognizer: public PatternRecognizer
{
	using SetCount = int;
	using IdentityInfo = std::pair<Meld, SetCount>;

public:
	RECOGNIZER_CONSTRUCTOR(IdenticalSequencesRecognizer);

	virtual void reset() override;
	virtual void check(const Pair& pair) override;
	virtual void check(const Meld& meld) override;
	virtual std::set<Pattern> recognize() override;

private:
	std::vector<IdentityInfo> identity_infos;
};
}
