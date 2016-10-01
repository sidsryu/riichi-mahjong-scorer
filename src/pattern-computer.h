#pragma once

#include <vector>
#include <memory>
#include <set>

enum class Pattern;
struct WiningHand;
class PlayerHand;
class WiningState;
class PatternRecognizer;
class Pair;
class Meld;

class PatternComputer
{
	using WiningHands = std::vector<WiningHand>;
	using PatternRecognizerPtr = std::unique_ptr<PatternRecognizer>;

public:
	PatternComputer(const PlayerHand& hand, const WiningState& state);
	virtual ~PatternComputer();

	std::set<Pattern> compute();

private:
	void resetRecognizer();
	void check(const WiningHand& hand);
	void check(const Pair& pair);
	void check(const Meld& meld);
	void recognize();
	void special(const PlayerHand& hand);

private:
	const PlayerHand& hand;
	const WiningState& state;
	std::vector<PatternRecognizerPtr> recognizers;	
	std::set<Pattern> highest_patterns;
};
