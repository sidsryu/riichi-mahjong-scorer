#include "wining-hand-counter.h"
#include "player-hand.h"
#include "hand-define.h"
#include "wining-state.h"
#include "tile-holder.h"
#include "type-define.h"
#include "tile-functor.h"
#include "tile-define.h"
#include <array>
#include <cassert>

using namespace std;

WiningHandCounter::WiningHandCounter(const PlayerHand& hand, const WiningState& state)
	: hand(hand)
	, state(state)
{}

void WiningHandCounter::calculate()
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
			auto chii_count = 0;
			auto is_wait_multi = false;
			for (auto m : it.melds)
			{
				if (!IsSame()(m.tiles[0], m.tiles[1]))
				{
					chii_count++;

					if ((IsSame()(m.tiles[0], it.last_tile) && !IsTerminal()(m.tiles[2])) ||
						(IsSame()(m.tiles[2], it.last_tile) && !IsTerminal()(m.tiles[0])))
					{
						is_wait_multi = true;
					}
				}
			}

			auto is_fu_pair = false;
			if (IsDragon()(it.pairs.front().tiles.front()) ||
				IsSame()(it.pairs.front().tiles.front(), state.ownWind()) ||
				IsSame()(it.pairs.front().tiles.front(), state.roundWind()))
			{
				is_fu_pair = true;
			}

			if (chii_count == 4 && is_wait_multi && !is_fu_pair)
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
				if (IsSame()(it.melds[i].tiles[0], it.melds[i].tiles[1])) continue;

				for (auto j = i + 1; j < it.melds.size(); j++)
				{
					if (IsSame()(it.melds[j].tiles[0], it.melds[j].tiles[1])) continue;

					if (IsSame()(it.melds[i].tiles[0], it.melds[j].tiles[0]))
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
			if (IsSame()(m.tiles.front(), Tile::WhiteDragon))
			{
				it.hands.insert(Hand::WhiteDragon);
			}

			if (IsSame()(m.tiles.front(), Tile::GreenDragon))
			{
				it.hands.insert(Hand::GreenDragon);
			}

			if (IsSame()(m.tiles.front(), Tile::RedDragon))
			{
				it.hands.insert(Hand::RedDragon);
			}

			if (IsSame()(m.tiles.front(), Tile::EastWind))
			{
				auto wind_count = 0;

				if (IsSame()(m.tiles.front(), state.roundWind()))
				{
					wind_count++;
				}

				if (IsSame()(m.tiles.front(), state.ownWind()))
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

			if (IsSame()(m.tiles.front(), Tile::SouthWind))
			{
				auto wind_count = 0;

				if (IsSame()(m.tiles.front(), state.roundWind()))
				{
					wind_count++;
				}

				if (IsSame()(m.tiles.front(), state.ownWind()))
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

			if (IsSame()(m.tiles.front(), Tile::WestWind))
			{
				auto wind_count = 0;

				if (IsSame()(m.tiles.front(), state.roundWind()))
				{
					wind_count++;
				}

				if (IsSame()(m.tiles.front(), state.ownWind()))
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

			if (IsSame()(m.tiles.front(), Tile::NorthWind))
			{
				auto wind_count = 0;

				if (IsSame()(m.tiles.front(), state.roundWind()))
				{
					wind_count++;
				}

				if (IsSame()(m.tiles.front(), state.ownWind()))
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
			if (!IsSimple()(m.tiles[0]))
			{
				is_all_simple = false;
			}
		}
		for (auto m : it.melds)
		{
			if (!IsSimple()(m.tiles[0]) || !IsSimple()(m.tiles[2]))
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
			if (!IsSame()(m.tiles[0], m.tiles[1]))
			{
				auto code = static_cast<int>(m.tiles[0]);
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

	if (holder.isNextTilePonOrKan())
	{
		ponBt(hand, holder);
	}

	if (holder.isNextTileChii())
	{
		chiiBt(hand, holder);
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
		if (IsSame()(it.tiles.front(), pair.tiles.front()))
		{
			return;
		}
	}
	hand.pairs.push_back(pair);

	bt(hand, holder);
}

void WiningHandCounter::ponBt(WiningHand hand, TileHolder holder)
{
	auto meld = holder.popNextPonOrKan();
	hand.melds.push_back(meld);

	bt(hand, holder);
}

void WiningHandCounter::chiiBt(WiningHand hand, TileHolder holder)
{
	auto meld = holder.popNextChii();	
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
