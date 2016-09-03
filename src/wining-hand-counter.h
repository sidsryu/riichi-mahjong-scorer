#pragma once

#include <set>

enum class Hand;

class WiningHandCounter
{
public:
	void add(Hand hand);
	bool hasHand(Hand hand) const;

private:
	std::set<Hand> hands;
};
