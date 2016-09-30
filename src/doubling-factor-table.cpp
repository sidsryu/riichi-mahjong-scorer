#include "doubling-factor-table.h"
#include "pattern-define.h"
#include "wining-state.h"
#include <algorithm>

const int LIMIT_HAND_FACTOR = 100;

DoublingFactorTable::DoublingFactorTable(const WiningState& state)
	: state(state)
{
	auto closed_hand_bonus = 0;
	if (state.isClosedHand())
	{
		closed_hand_bonus = 1;
	}

	factor_table.insert({ Pattern::ReadyHand, 1 });	
	factor_table.insert({ Pattern::OneShot, 1 });
	factor_table.insert({ Pattern::LastTileFromTheWall, 1 });
	factor_table.insert({ Pattern::LastDiscard, 1 });
	factor_table.insert({ Pattern::DeadWallDraw, 1 });
	factor_table.insert({ Pattern::RobbingQuad, 1 });
	factor_table.insert({ Pattern::SelfDrawn, 1 });
	factor_table.insert({ Pattern::OneSetOfIdenticalSequences, 1 });
	factor_table.insert({ Pattern::NoPointsHand, 1 });
	factor_table.insert({ Pattern::WhiteDragon, 1 });
	factor_table.insert({ Pattern::GreenDragon, 1 });
	factor_table.insert({ Pattern::RedDragon, 1 });
	factor_table.insert({ Pattern::EastWind, 1 });
	factor_table.insert({ Pattern::SouthWind, 1 });
	factor_table.insert({ Pattern::WestWind, 1 });
	factor_table.insert({ Pattern::NorthWind, 1 });
	factor_table.insert({ Pattern::AllSimples, 1 });

	factor_table.insert({ Pattern::ThreeColourStraights, 1 + closed_hand_bonus });
	factor_table.insert({ Pattern::Straight, 1 + closed_hand_bonus });
	factor_table.insert({ Pattern::TerminalOrHonorInEachSet, 1 + closed_hand_bonus });		

	factor_table.insert({ Pattern::DoubleEastWind, 2 });
	factor_table.insert({ Pattern::DoubleSouthWind, 2 });
	factor_table.insert({ Pattern::DoubleWestWind, 2 });
	factor_table.insert({ Pattern::DoubleNorthWind, 2 });
	factor_table.insert({ Pattern::DoubleReady, 2 });
	factor_table.insert({ Pattern::SevenPairs, 2 });
	factor_table.insert({ Pattern::AllTriplets, 2 });
	factor_table.insert({ Pattern::ThreeClosedTriplets, 2 });
	factor_table.insert({ Pattern::ThreeColourTriplets, 2 });
	factor_table.insert({ Pattern::ThreeQuads, 2 });
	factor_table.insert({ Pattern::LittleThreeDragons, 2 });
	factor_table.insert({ Pattern::AllTerminalsAndHornors, 2 });

	factor_table.insert({ Pattern::HalfFlush, 2 + closed_hand_bonus });
	factor_table.insert({ Pattern::TerminalInEachSet, 2 + closed_hand_bonus });

	factor_table.insert({ Pattern::TwoSetsOfIdenticalSequences, 3 });	

	factor_table.insert({ Pattern::Flush, 6 });

	factor_table.insert({ Pattern::HeavenlyHand, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::EarthlyHand, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::FourClosedTriplets, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::ThirteenOrphans, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::NineGates, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::AllGreen, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::AllHonors, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::AllTerminals, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::BigThreeDragons, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::LittleFourWinds, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::BigFourWinds, LIMIT_HAND_FACTOR });
	factor_table.insert({ Pattern::FourQuads, LIMIT_HAND_FACTOR });
}

int DoublingFactorTable::total(const std::set<Pattern>& patterns) const
{
	auto total_factor { 0 };
	for (auto it : patterns)
	{
		total_factor += factor(it);
	}

	return std::min(total_factor, LIMIT_HAND_FACTOR);
}

int DoublingFactorTable::factor(Pattern pattern) const
{
	auto it = factor_table.find(pattern);
	if (it == factor_table.end()) return 0;

	return it->second;	
}
