#pragma once

#include <set>
#include <vector>

#include "wining-hand.h"

enum class Hand;
class PlayerHand;
class TileHolder;

class WiningHandCounter
{
public:
	WiningHandCounter(const PlayerHand& hand);
	void calculate();

	bool hasHand(Hand hand) const;
	bool isNoHand() const;

private:
	void addWiningHand(WiningHand hand);
	void bt(WiningHand hand, TileHolder holder);
	void pairBt(WiningHand hand, TileHolder holder);
	void ponBt(WiningHand hand, TileHolder holder);
	void chiiBt(WiningHand hand, TileHolder holder);

private:
	const PlayerHand& hand;
	std::set<Hand> hands;
	std::vector<WiningHand> wining_hands;
};
