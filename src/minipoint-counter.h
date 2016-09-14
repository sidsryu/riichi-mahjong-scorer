#pragma once

struct WiningHand;
class WiningState;

class MinipointCounter
{
public:
	MinipointCounter(const WiningHand& hand, const WiningState& state);
	int total(bool is_round_up = true);

private:
	int roundUp(int point) const;
	bool isNoPointsHandSelfPick() const;
	bool isSevenPairs() const;	
	void calculateMelds();
	void calculatePair();
	void calculateWait();	
	void calculateWining();

private:
	const WiningHand& hand;
	const WiningState& state;
	int point { 0 };
};
