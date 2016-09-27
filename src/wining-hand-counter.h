#pragma once

#include <set>
#include <vector>

enum class Pattern;
struct WiningHand;
struct DoublingFactorReport;
class PlayerHand;
class TileHolder;
class WiningState;

class WiningHandCounter
{
public:
	WiningHandCounter(const PlayerHand& hand, const WiningState& state);
	DoublingFactorReport compute();

private:
	const PlayerHand& hand;
	const WiningState& state;	
};
