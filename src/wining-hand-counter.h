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
	void addWiningHand(WiningHand hand);
	void bt(WiningHand hand, TileHolder holder);
	void pairBt(WiningHand hand, TileHolder holder);
	void tripletOrQuadBt(WiningHand hand, TileHolder holder);
	void sequenceBt(WiningHand hand, TileHolder holder);

private:
	const PlayerHand& hand;
	const WiningState& state;
	std::set<Pattern> patterns;
	std::vector<WiningHand> wining_hands;
};
