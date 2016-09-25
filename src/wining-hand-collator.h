#pragma once

#include <vector>

struct WiningHand;
class PlayerHand;
class TileHolder;

class WiningHandCollator
{
	using WiningHands = std::vector<WiningHand>;
public:
	WiningHandCollator(const PlayerHand& hand);
	WiningHands collate();

private:
	void backtrack(const WiningHand& extended_hand, const TileHolder& extended_holder);
	void backtrackPair(WiningHand extended_hand, TileHolder extended_holder);
	void backtrackTripletOrQuad(WiningHand extended_hand, TileHolder extended_holder);
	void backtrackSequence(WiningHand extended_hand, TileHolder extended_holder);

private:
	const PlayerHand& hand;
	WiningHands wining_hands;
};
