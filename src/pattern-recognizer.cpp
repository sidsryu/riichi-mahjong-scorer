#include "pattern-recognizer.h"

namespace mahjong {
PatternRecognizer::PatternRecognizer(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}
}
