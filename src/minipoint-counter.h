#pragma once

struct WiningHand;
class WiningState;

class MinipointCounter
{
public:
	MinipointCounter(const WiningHand& hand, const WiningState& state);
	int total(bool is_round_up = true) const;

private:
	int roundUp(int total) const;

private:
	const WiningHand& hand;
	const WiningState& state;
};
