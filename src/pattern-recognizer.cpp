#include "pattern-recognizer.h"

PatternRecognizer::PatternRecognizer(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}
