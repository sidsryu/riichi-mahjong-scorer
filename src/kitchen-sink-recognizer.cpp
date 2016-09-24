#include "kitchen-sink-recognizer.h"
#include "wining-state.h"
#include "pattern-define.h"
#include "tile-define.h"
#include "tile-functor.h"
#include "player-hand.h"
#include "pair.h"
#include "meld.h"
#include <array>

using namespace std;

KitchenSinkRecognizer::KitchenSinkRecognizer(const WiningState& state)
	: HandRecognizer(state)
{}

void KitchenSinkRecognizer::reset()
{
	wining_hand = WiningHand();
}

void KitchenSinkRecognizer::check(const Pair& pair)
{
	wining_hand.pairs.push_back(pair);
}

void KitchenSinkRecognizer::check(const Meld& meld)
{
	wining_hand.melds.push_back(meld);
}

set<Pattern> KitchenSinkRecognizer::recognize()
{
	auto it = wining_hand;

	if (state.isClosedHand())
	{
		auto sequence_count = 0;
		auto is_wait_multi = false;
		for (auto m : it.melds)
		{
			if (m.isSequence())
			{
				sequence_count++;

				if (m.isMultiWait(state.lastTile()))
				{
					is_wait_multi = true;
				}
			}
		}

		auto is_fu_pair = false;
		for (auto m : it.pairs)
		{
			if (m.isValuePair(state))
			{
				is_fu_pair = true;
			}
		}

		if (sequence_count == 4 && is_wait_multi && !is_fu_pair)
		{
			it.patterns.insert(Pattern::NoPointsHand);
		}
	}

	if (7 == it.pairs.size())
	{
		it.patterns.insert(Pattern::SevenPairs);
	}

	if (state.isClosedHand())
	{
		auto identical_sequence_count = 0;
		for (size_t i = 0; i < it.melds.size(); i++)
		{
			for (auto j = i + 1; j < it.melds.size(); j++)
			{
				if (it.melds[i].isSame(it.melds[j]))
				{
					identical_sequence_count++;
				}
			}
		}

		if (1 == identical_sequence_count)
		{
			it.patterns.insert(Pattern::OneSetOfIdenticalSequences);
		}
		else if (2 == identical_sequence_count)
		{
			it.patterns.insert(Pattern::TwoSetsOfIdenticalSequences);
		}
	}

	for (auto m : it.melds)
	{
		if (m.isContain(Tile::WhiteDragon))
		{
			it.patterns.insert(Pattern::WhiteDragon);
		}

		if (m.isContain(Tile::GreenDragon))
		{
			it.patterns.insert(Pattern::GreenDragon);
		}

		if (m.isContain(Tile::RedDragon))
		{
			it.patterns.insert(Pattern::RedDragon);
		}

		if (m.isContain(Tile::EastWind))
		{
			auto wind_count = 0;

			if (IsSame()(Tile::EastWind, state.roundWind()))
			{
				wind_count++;
			}

			if (IsSame()(Tile::EastWind, state.seatWind()))
			{
				wind_count++;
			}

			if (1 == wind_count)
			{
				it.patterns.insert(Pattern::EastWind);
			}
			else if (2 == wind_count)
			{
				it.patterns.insert(Pattern::DoubleEastWind);
			}
		}

		if (m.isContain(Tile::SouthWind))
		{
			auto wind_count = 0;

			if (IsSame()(Tile::SouthWind, state.roundWind()))
			{
				wind_count++;
			}

			if (IsSame()(Tile::SouthWind, state.seatWind()))
			{
				wind_count++;
			}

			if (1 == wind_count)
			{
				it.patterns.insert(Pattern::SouthWind);
			}
			else if (2 == wind_count)
			{
				it.patterns.insert(Pattern::DoubleSouthWind);
			}
		}

		if (m.isContain(Tile::WestWind))
		{
			auto wind_count = 0;

			if (IsSame()(Tile::WestWind, state.roundWind()))
			{
				wind_count++;
			}

			if (IsSame()(Tile::WestWind, state.seatWind()))
			{
				wind_count++;
			}

			if (1 == wind_count)
			{
				it.patterns.insert(Pattern::WestWind);
			}
			else if (2 == wind_count)
			{
				it.patterns.insert(Pattern::DoubleWestWind);
			}
		}

		if (m.isContain(Tile::NorthWind))
		{
			auto wind_count = 0;

			if (IsSame()(Tile::NorthWind, state.roundWind()))
			{
				wind_count++;
			}

			if (IsSame()(Tile::NorthWind, state.seatWind()))
			{
				wind_count++;
			}

			if (1 == wind_count)
			{
				it.patterns.insert(Pattern::NorthWind);
			}
			else if (2 == wind_count)
			{
				it.patterns.insert(Pattern::DoubleNorthWind);
			}
		}
	}

	bool is_all_simple = true;
	for (auto m : it.pairs)
	{
		if (!m.isSimples())
		{
			is_all_simple = false;
		}
	}
	for (auto m : it.melds)
	{
		if (!m.isSimples())
		{
			is_all_simple = false;
		}
	}
	if (is_all_simple)
	{
		it.patterns.insert(Pattern::AllSimples);
	}

	array<array<bool, 3>, 9> straight_checker {};
	for (auto m : it.melds)
	{
		if (m.isSequence())
		{
			auto code = static_cast<int>(m.frontTile());
			auto suit = code / 100;
			auto number = code / 10 % 10;

			straight_checker[number - 1][suit - 1] = true;
		}
	}
	for (auto c : straight_checker)
	{
		if (c[0] && c[1] && c[2])
		{
			it.patterns.insert(Pattern::ThreeColourStraights);
			break;
		}
	}

	if ((straight_checker[0][0] &&
		straight_checker[3][0] &&
		straight_checker[6][0]) ||
		(straight_checker[0][1] &&
			straight_checker[3][1] &&
			straight_checker[6][1]) ||
			(straight_checker[0][2] &&
				straight_checker[3][2] &&
				straight_checker[6][2]))
	{
		it.patterns.insert(Pattern::Straight);
	}

	auto triplet_count = 0;
	auto closed_triplet_count = 0;
	auto closed_modify = 0;
	array<int, 9> triplets_colour_checker {};
	auto quad_count = 0;
	for (auto m : it.melds)
	{
		if (m.isQuad())
		{
			quad_count++;
		}

		if (m.isTripletOrQuad())
		{
			auto number = static_cast<int>(m.frontTile()) / 10 % 10;
			triplets_colour_checker[number - 1]++;

			triplet_count++;

			if (!m.isOpen())
			{
				closed_triplet_count++;

				if (m.isContain(state.lastTile()))
				{
					closed_modify--;
				}
			}
		}
		else if (!m.isOpen())
		{
			if (m.isContain(state.lastTile()))
			{
				closed_modify++;
			}
		}
	}
	if (closed_modify < 0) closed_triplet_count--;

	if (closed_triplet_count == 4)
	{
	}
	else
	{
		if (closed_triplet_count == 3)
		{
			it.patterns.insert(Pattern::ThreeClosedTriplets);
		}

		if (triplet_count == 4)
		{
			it.patterns.insert(Pattern::AllTriplets);
		}
	}

	for (auto c : triplets_colour_checker)
	{
		if (c == 3)
		{
			it.patterns.insert(Pattern::ThreeColourTriplets);
		}
	}

	if (quad_count == 3)
	{
		it.patterns.insert(Pattern::ThreeQuads);
	}

	auto is_terminal_or_honor_in_each_set = true;
	auto is_terminal_in_each_set = true;
	auto is_all_terminal_or_honor = true;
	for (auto m : it.pairs)
	{
		if (m.isSimples())
		{
			is_terminal_or_honor_in_each_set = false;
			is_terminal_in_each_set = false;
			is_all_terminal_or_honor = false;
		}
	}
	for (auto m : it.melds)
	{
		if (m.isTripletOrQuad())
		{
			if (m.isSimples())
			{
				is_terminal_or_honor_in_each_set = false;
				is_terminal_in_each_set = false;
				is_all_terminal_or_honor = false;
			}
			else if (m.isHonors())
			{
				is_terminal_in_each_set = false;
			}
		}
		else
		{
			is_all_terminal_or_honor = false;

			if (!m.hasTerminal())
			{
				is_terminal_or_honor_in_each_set = false;
				is_terminal_in_each_set = false;
			}
		}
	}
	if (is_terminal_or_honor_in_each_set)
	{
		it.patterns.insert(Pattern::TerminalOrHonorInEachSet);
	}
	if (is_terminal_in_each_set)
	{
		it.patterns.insert(Pattern::TerminalInEachSet);
	}
	if (is_all_terminal_or_honor)
	{
		it.patterns.insert(Pattern::AllTerminalsAndHornors);
	}

	auto dragon_count = 0;
	auto is_dragon_pair = false;
	for (auto m : it.pairs)
	{
		if (m.isDragons())
		{
			is_dragon_pair = true;
		}
	}
	for (auto m : it.melds)
	{
		if (m.isDragons())
		{
			dragon_count++;
		}
	}
	if (is_dragon_pair && dragon_count == 2)
	{
		it.patterns.insert(Pattern::LittleThreeDragons);
	}

	auto suit_number = 0;
	auto is_flush = true;
	auto is_honor = false;
	for (auto m : it.pairs)
	{
		if (m.isHonors())
		{
			is_honor = true;
		}
		else
		{
			auto suit = static_cast<int>(m.frontTile()) / 100;
			if (suit_number == 0) suit_number = suit;
			if (suit_number != suit)
			{
				is_flush = false;
			}
		}
	}
	for (auto m : it.melds)
	{
		if (m.isHonors())
		{
		}
		else
		{
			auto suit = static_cast<int>(m.frontTile()) / 100;
			if (suit_number == 0) suit_number = suit;
			if (suit_number != suit)
			{
				is_flush = false;
			}
		}
	}
	if (is_flush)
	{
		if (is_honor)
		{
			it.patterns.insert(Pattern::HalfFlush);
		}
		else
		{
			it.patterns.insert(Pattern::Flush);
		}
	}

	return it.patterns;
}
