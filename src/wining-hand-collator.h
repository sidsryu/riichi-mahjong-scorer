#pragma once

#include <vector>

enum class Tile;
struct WiningHand;
class PlayerHand;
class TileHolder;

class WiningHandCollator
{
	using WiningHands = std::vector<WiningHand>;

public:
	WiningHands collate(const PlayerHand& hand);

private:
	void backtrack(const WiningHand& extended_hand, const TileHolder& extended_holder);
	void backtrackPair(WiningHand extended_hand, TileHolder extended_holder);
	void backtrackTripletOrQuad(WiningHand extended_hand, TileHolder extended_holder);
	void backtrackSequence(WiningHand extended_hand, TileHolder extended_holder);

private:
	WiningHands wining_hands;
};
