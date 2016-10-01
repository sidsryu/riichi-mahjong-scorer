#pragma once

#include "wining-hand.h"
#include <vector>
#include <memory>
#include <set>

namespace mahjong {
enum class Pattern;
class PlayerHand;
class WiningState;
class PatternRecognizer;
class Pair;
class Meld;

class PatternComputer
{
	using WiningHands = std::vector<WiningHand>;
	using WiningPatterns = std::set<Pattern>;
	using PatternRecognizerPtr = std::unique_ptr<PatternRecognizer>;

public:
	PatternComputer(const PlayerHand& hand, const WiningState& state);
	virtual ~PatternComputer();

	void compute(WiningPatterns& out_patterns, WiningHand& out_wining_hand);

private:
	void resetRecognizer();
	void check(const WiningHand& hand);
	void check(const Pair& pair);
	void check(const Meld& meld);
	WiningPatterns recognize();
	void special(const PlayerHand& hand);
	void setHighest(const WiningHand& hand, const WiningPatterns& patterns);

private:
	const PlayerHand& hand;
	const WiningState& state;
	std::vector<PatternRecognizerPtr> recognizers;
	WiningPatterns highest_patterns;
	WiningHand highest_wining_hand;
};
}
