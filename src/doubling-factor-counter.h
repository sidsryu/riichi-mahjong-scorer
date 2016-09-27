#pragma once

struct DoublingFactorReport;
class PlayerHand;
class WiningState;

class DoubligFactorCounter
{
public:
	DoubligFactorCounter(const PlayerHand& hand, const WiningState& state);
	DoublingFactorReport report();

private:
	const PlayerHand& hand;
	const WiningState& state;	
};
