#pragma once

#include <set>
#include <vector>

enum class Pattern;
struct WiningHand;
class PlayerHand;
class TileHolder;
class WiningState;

class WiningHandCounter
{
public:
	WiningHandCounter(const PlayerHand& hand, const WiningState& state);
	void compute();

	bool hasPattern(Pattern pattern) const;
	bool isPattenEmpty() const;	

private:
	const PlayerHand& hand;
	const WiningState& state;
	std::set<Pattern> patterns;
	std::vector<WiningHand> wining_hands;
};
