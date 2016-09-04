#pragma once

#include <set>

enum class Hand;
class PlayerHand;

class WiningHandCounter
{
public:
	WiningHandCounter(const PlayerHand& hand);
	void calculate();

	bool hasHand(Hand hand) const;
	bool isNoHand() const;

private:
	const PlayerHand& hand;
	std::set<Hand> hands;
};
