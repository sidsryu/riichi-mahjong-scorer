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
	PatternComputer(const WiningState& state);
	virtual ~PatternComputer();

	std::set<Pattern> compute(const PlayerHand& hand);

private:
	void resetRecognizer();
	void check(const WiningHand& hand);
	void check(const Pair& pair);
	void check(const Meld& meld);
	void recognize();

private:
	const WiningState& state;
	std::vector<PatternRecognizerPtr> recognizers;	
	std::set<Pattern> highest_patterns;
};
