#pragma once

#include <set>

enum class Pattern;
class Pair;
class Meld;
class PlayerHand;
class WiningState;

class PatternRecognizer
{
public:
	PatternRecognizer(const PlayerHand& hand, const WiningState& state);
	virtual ~PatternRecognizer() = default;

	virtual void reset() = 0;
	virtual void check(const Pair& pair) = 0;
	virtual void check(const Meld& meld) = 0;
	virtual std::set<Pattern> recognize() = 0;

protected:
	const PlayerHand& hand;
	const WiningState& state;
};

#define RECOGNIZER_CONSTRUCTOR(class_name)\
	class_name(const PlayerHand& hand, const WiningState& state)\
		: PatternRecognizer(hand, state)\
	{}
