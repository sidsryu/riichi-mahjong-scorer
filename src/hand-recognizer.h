#pragma once

#include <set>

enum class Pattern;
class Pair;
class Meld;
class PlayerHand;
class WiningState;

class HandRecognizer
{
public:
	HandRecognizer(const WiningState& state);
	virtual ~HandRecognizer() = default;

	virtual void reset() = 0;
	virtual void check(const Pair& pair) = 0;
	virtual void check(const Meld& meld) = 0;
	virtual std::set<Pattern> recognize() = 0;

protected:
	const WiningState& state;
};
