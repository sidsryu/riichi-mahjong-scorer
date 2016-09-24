#include "wining-hand-counter.h"
#include "player-hand.h"
#include "hand-define.h"
#include "wining-state.h"
#include "tile-holder.h"
#include "wining-Hand.h"
#include "tile-functor.h"
#include "tile-define.h"
#include "pair.h"
#include "meld.h"
#include <array>
#include <cassert>

using namespace std;

WiningHandCounter::WiningHandCounter(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

void WiningHandCounter::compute()
{
	wining_hands.clear();
	hands.clear();

	auto tile_holder = hand.makeHandHolder();

	WiningHand wining_hand;
	wining_hand.last_tile = hand.lastTile();

	bt(wining_hand, tile_holder);

	for (auto& it : wining_hands)
	{		
		if (state.isDoubleRiichi())
		{
			it.hands.insert(Hand::DoubleReady);
		}

		if (state.isRiichi())
		{
			it.hands.insert(Hand::ReadyHand);
		}

		if (!hand.isClaim() && !state.isRon())
		{
			it.hands.insert(Hand::SelfPick);
		}

		if (!hand.isClaim())
		{
			auto sequence_count = 0;
			auto is_wait_multi = false;
			for (auto m : it.melds)
			{
				if (m.isSequence())
				{
					sequence_count++;

					if (m.isMultiWait(it.last_tile))
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
				it.hands.insert(Hand::NoPointsHand);
			}
		}

		if (7 == it.pairs.size())
		{
			it.hands.insert(Hand::SevenPairs);
		}

		if (!hand.isClaim())
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
				it.hands.insert(Hand::OneSetOfIdenticalSequences);
			}
			else if (2 == identical_sequence_count)
			{
				it.hands.insert(Hand::TwoSetsOfIdenticalSequences);
			}
		}

		for (auto m : it.melds)
		{
			if (m.isContain(Tile::WhiteDragon))
			{
				it.hands.insert(Hand::WhiteDragon);
			}

			if (m.isContain(Tile::GreenDragon))
			{
				it.hands.insert(Hand::GreenDragon);
			}

			if (m.isContain(Tile::RedDragon))
			{
				it.hands.insert(Hand::RedDragon);
			}

			if (m.isContain(Tile::EastWind))
			{
				auto wind_count = 0;

				if (IsSame()(Tile::EastWind, state.roundWind()))
				{
					wind_count++;
				}

				if (IsSame()(Tile::EastWind, state.ownWind()))
				{
					wind_count++;
				}

				if (1 == wind_count)
				{
					it.hands.insert(Hand::EastWind);
				}
				else if (2 == wind_count)
				{
					it.hands.insert(Hand::DoubleEastWind);
				}
			}

			if (m.isContain(Tile::SouthWind))
			{
				auto wind_count = 0;

				if (IsSame()(Tile::SouthWind, state.roundWind()))
				{
					wind_count++;
				}

				if (IsSame()(Tile::SouthWind, state.ownWind()))
				{
					wind_count++;
				}

				if (1 == wind_count)
				{
					it.hands.insert(Hand::SouthWind);
				}
				else if (2 == wind_count)
				{
					it.hands.insert(Hand::DoubleSouthWind);
				}
			}

			if (m.isContain(Tile::WestWind))
			{
				auto wind_count = 0;

				if (IsSame()(Tile::WestWind, state.roundWind()))
				{
					wind_count++;
				}

				if (IsSame()(Tile::WestWind, state.ownWind()))
				{
					wind_count++;
				}

				if (1 == wind_count)
				{
					it.hands.insert(Hand::WestWind);
				}
				else if (2 == wind_count)
				{
					it.hands.insert(Hand::DoubleWestWind);
				}
			}

			if (m.isContain(Tile::NorthWind))
			{
				auto wind_count = 0;

				if (IsSame()(Tile::NorthWind, state.roundWind()))
				{
					wind_count++;
				}

				if (IsSame()(Tile::NorthWind, state.ownWind()))
				{
					wind_count++;
				}

				if (1 == wind_count)
				{
					it.hands.insert(Hand::NorthWind);
				}
				else if (2 == wind_count)
				{
					it.hands.insert(Hand::DoubleNorthWind);
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
			it.hands.insert(Hand::AllSimples);
		}

		array<array<bool, 3>, 9> straight_checker {};
		for (auto m : it.melds)
		{
			if (m.isSequence())
			{
				auto code = static_cast<int>(m.frontTile());
				auto suit = code / 100;
				auto number = code / 10 % 10;

				straight_checker[number-1][suit-1] = true;
			}
		}
		for (auto c : straight_checker)
		{
			if (c[0] && c[1] && c[2])			
			{
				it.hands.insert(Hand::ThreeColourStraights);
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
			it.hands.insert(Hand::Straight);
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
				triplets_colour_checker[number-1]++;

				triplet_count++;

				if (!m.isOpen())
				{
					closed_triplet_count++;

					if (m.isContain(it.last_tile))
					{
						closed_modify--;
					}
				}
			}
			else if (!m.isOpen())
			{
				if (m.isContain(it.last_tile))
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
				it.hands.insert(Hand::ThreeClosedTriplets);
			}

			if (triplet_count == 4)
			{
				it.hands.insert(Hand::AllTripletHand);
			}
		}

		for (auto c : triplets_colour_checker)
		{
			if (c == 3)
			{
				it.hands.insert(Hand::ThreeColourTriplets);
			}
		}

		if (quad_count == 3)
		{
			it.hands.insert(Hand::ThreeQuads);
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
			it.hands.insert(Hand::TerminalOrHonorInEachSet);
		}
		if (is_terminal_in_each_set)
		{
			it.hands.insert(Hand::TerminalInEachSet);
		}
		if (is_all_terminal_or_honor)
		{
			it.hands.insert(Hand::AllTerminalsAndHornors);
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
			it.hands.insert(Hand::LittleThreeDragons);
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
				it.hands.insert(Hand::HalfFlush);
			}
			else
			{
				it.hands.insert(Hand::Flush);
			}
		}
	}

	for (auto it : wining_hands)
	{
		if (wining_hands.front().hands.empty()) continue;

		if (hands.empty())
		{
			hands = it.hands;
		}
		else if ((int)*hands.rbegin() < (int)*it.hands.rbegin())
		{
			hands = it.hands;
		}		
	}
}

void WiningHandCounter::bt(WiningHand hand, TileHolder holder)
{
	if (holder.empty())
	{
		addWiningHand(hand);
		return;
	}

	if (holder.isNextTilePair())
	{
		pairBt(hand, holder);
	}

	if (holder.isNextTileTripletOrQuad())
	{
		tripletOrQuadBt(hand, holder);
	}

	if (holder.isNextTileSequence())
	{
		sequenceBt(hand, holder);
	}
}

void WiningHandCounter::pairBt(WiningHand hand, TileHolder holder)
{
	if (1 <= hand.pairs.size() && 1 <= hand.melds.size())
	{
		return;
	}

	auto pair = holder.popNextPair();
	for (auto it : hand.pairs)
	{
		if (it.isSame(pair))
		{
			return;
		}
	}
	hand.pairs.push_back(pair);

	bt(hand, holder);
}

void WiningHandCounter::tripletOrQuadBt(WiningHand hand, TileHolder holder)
{
	auto meld = holder.popNextTripletOrQuad();
	hand.melds.push_back(meld);

	bt(hand, holder);
}

void WiningHandCounter::sequenceBt(WiningHand hand, TileHolder holder)
{
	auto meld = holder.popNextSequence();	
	hand.melds.push_back(meld);

	bt(hand, holder);
}

void WiningHandCounter::addWiningHand(WiningHand hand)
{
	wining_hands.push_back(hand);
}

bool WiningHandCounter::hasHand(Hand hand) const
{
	auto it = hands.find(hand);
	return it != hands.end();
}

bool WiningHandCounter::isNoHand() const
{
	return 0 == hands.size();
}
