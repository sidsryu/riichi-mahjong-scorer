#pragma once

#include <vector>
#include <memory>
#include <set>

enum class Pattern;
struct WiningHand;
class PlayerHand;
class WiningState;
class HandRecognizer;
class Pair;
class Meld;

class HandComputer
{
	using WiningHands = std::vector<WiningHand>;
	using HandRecognizerPtr = std::unique_ptr<HandRecognizer>;

public:
	HandComputer(const WiningState& state);
	virtual ~HandComputer();

	std::set<Pattern> compute(const PlayerHand& hand);

private:
	void resetRecognizer();
	void check(const WiningHand& hand);
	void check(const Pair& pair);
	void check(const Meld& meld);
	void recognize();

private:
	const WiningState& state;
	std::vector<HandRecognizerPtr> recognizers;	
	std::set<Pattern> highest_patterns;
};
