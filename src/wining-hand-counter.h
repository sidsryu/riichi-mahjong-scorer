#pragma once

#include <set>
#include <vector>

enum class Hand;
struct WiningHand;
class PlayerHand;
class TileHolder;
class WiningState;

class WiningHandCounter
{
public:
	WiningHandCounter(const PlayerHand& hand, const WiningState& state);
	void calculate();

	bool hasHand(Hand hand) const;
	bool isNoHand() const;

private:
	void addWiningHand(WiningHand hand);
	void bt(WiningHand hand, TileHolder holder);
	void pairBt(WiningHand hand, TileHolder holder);
	void tripletOrQuadBt(WiningHand hand, TileHolder holder);
	void sequenceBt(WiningHand hand, TileHolder holder);

private:
	const PlayerHand& hand;
	const WiningState& state;
	std::set<Hand> hands;
	std::vector<WiningHand> wining_hands;
};
