#include "CppUTest/TestHarness.h"
#include "wining-hand-counter.h"
#include "wining-state.h"
#include "player-hand.h"
#include "tile-functor.h"
#include "hand-define.h"
#include "tile-define.h"
#include "wining-hand.h"
#include "pair.h"
#include "meld.h"
#include <cassert>

TEST_GROUP(WiningHandCounterTest)
{
	PlayerHand h;
	WiningState s;
	WiningHandCounter w { h, s };

	void addPair(Tile tile)
	{
		h.add(tile);
		h.add(tile);
	}

	void addPon(Tile tile, bool is_open)
	{
		h.add(tile);
		h.add(tile);
		h.add(tile);

		if (is_open)
		{
			h.bindPon({ tile, tile, tile });
		}
	}

	void addChii(Tile tile, bool is_open)
	{
		auto next_tile = NextTile()(tile);
		auto last_tile = NextTile()(next_tile);

		h.add(tile);
		h.add(next_tile);
		h.add(last_tile);

		if (is_open)
		{
			h.bindChii({ tile, next_tile, last_tile });
		}
	}

	void addKan(Tile tile, bool is_open)
	{
		h.add(tile);
		h.add(tile);
		h.add(tile);
		h.add(tile);

		if (is_open)
		{
			h.bindKan({ tile,tile,tile,tile });
		}
		else
		{
			h.bindCloseKan({ tile,tile,tile,tile });
		}		
	}
};

TEST(WiningHandCounterTest, SevenPairs)
{
	addPair(Tile::EastWind);
	addPair(Tile::NorthWind);
	addPair(Tile::ThreeOfCharacters);
	addPair(Tile::NineOfCircles);
	addPair(Tile::OneOfBamboos);
	addPair(Tile::GreenDragon);
	addPair(Tile::OneOfCharacters);
	w.calculate();

	CHECK(w.hasHand(Hand::SevenPairs));
}

TEST(WiningHandCounterTest, Not_SevenPairs_FourSuit)
{
	addPair(Tile::EastWind);
	addPair(Tile::NorthWind);
	addPair(Tile::ThreeOfCharacters);
	addPair(Tile::NineOfCircles);
	addPair(Tile::OneOfBamboos);
	addPair(Tile::GreenDragon);
	addPair(Tile::GreenDragon);
	w.calculate();

	CHECK(!w.hasHand(Hand::SevenPairs));
}

TEST(WiningHandCounterTest, NoPointsHand)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfBamboos, false);
	addChii(Tile::SevenOfCharacters, false);

	w.calculate();

	CHECK(w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, Not_NoPointsHand_Open)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters, true);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfBamboos, false);
	addChii(Tile::SevenOfCharacters, false);

	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, Not_NoPointsHand_NotMultiWait)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfBamboos, false);

	h.add(Tile::NineOfCircles);
	h.add(Tile::EightOfCircles);
	h.add(Tile::SevenOfCircles);

	w.calculate();

	CHECK(!w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, Not_NoPointsHand_DragonPair)
{
	addPair(Tile::WhiteDragon);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfBamboos, false);
	addChii(Tile::SevenOfCharacters, false);

	w.calculate();

	CHECK(!w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, NoPointsHand_ScoringWindPair)
{
	s.setRountWind(Tile::EastWind);

	addPair(Tile::EastWind);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfBamboos, false);
	addChii(Tile::SevenOfCharacters, false);

	w.calculate();

	CHECK(!w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, OneSetOfIdenticalSequences)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfCircles, false);
	addPon(Tile::NineOfBamboos, false);

	w.calculate();

	CHECK(w.hasHand(Hand::OneSetOfIdenticalSequences));
}

TEST(WiningHandCounterTest, Not_OneSetOfIdenticalSequences_Open)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfCircles, false);
	addPon(Tile::NineOfBamboos, true);

	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, ThreeColourStraights)
{
	addPair(Tile::WestWind);
	addChii(Tile::TwoOfCharacters, false);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfBamboos, false);
	addChii(Tile::SevenOfCharacters, true);
	
	w.calculate();

	CHECK(w.hasHand(Hand::ThreeColourStraights));
}

TEST(WiningHandCounterTest, Straight)
{
	addPair(Tile::WestWind);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::FourOfCharacters, false);
	addChii(Tile::SevenOfCharacters, false);
	addPon(Tile::OneOfBamboos, false);

	w.calculate();

	CHECK(w.hasHand(Hand::Straight));
}

TEST(WiningHandCounterTest, TwoSetsOfIdenticalSequences)
{
	addPair(Tile::WestWind);
	addChii(Tile::TwoOfCharacters, false);
	addChii(Tile::TwoOfCharacters, false);
	addChii(Tile::ThreeOfCircles, false);
	addChii(Tile::ThreeOfCircles, false);

	w.calculate();

	CHECK(w.hasHand(Hand::TwoSetsOfIdenticalSequences));
	CHECK(!w.hasHand(Hand::SevenPairs));
}

TEST(WiningHandCounterTest, Not_TwoSetsOfIdenticalSequences_Open)
{
	addPair(Tile::WestWind);
	addChii(Tile::TwoOfCharacters, false);
	addChii(Tile::TwoOfCharacters, false);
	addChii(Tile::ThreeOfCircles, false);
	addChii(Tile::ThreeOfCircles, false);

	h.bindChii({
		Tile::ThreeOfCircles,
		Tile::FourOfCircles,
		Tile::FiveOfCircles
	});

	w.calculate();

	CHECK(!w.hasHand(Hand::TwoSetsOfIdenticalSequences));
}

TEST(WiningHandCounterTest, AllTripletHand)
{
	addPair(Tile::WestWind);
	addPon(Tile::OneOfCharacters, true);
	addPon(Tile::TwoOfCircles, true);
	addPon(Tile::ThreeOfBamboos, false);
	addPon(Tile::SevenOfCharacters, false);
	
	w.calculate();

	CHECK(w.hasHand(Hand::AllTripletHand));
}

TEST(WiningHandCounterTest, ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addPon(Tile::OneOfCharacters, false);
	addPon(Tile::TwoOfCircles, false);
	addPon(Tile::ThreeOfBamboos, false);
	addChii(Tile::SevenOfCharacters, false);

	w.calculate();

	CHECK(w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, Not_ThreeClosedTriplets_Ron)
{
	addPair(Tile::WestWind);	
	addChii(Tile::SevenOfCharacters, false);
	addPon(Tile::OneOfCharacters, false);
	addPon(Tile::TwoOfCircles, false);	
	addPon(Tile::ThreeOfBamboos, false);	

	s.setRon();
	w.calculate();

	CHECK(!w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, ThreeClosedTriplets_Ron)
{
	addPair(Tile::WestWind);	
	addPon(Tile::OneOfCharacters, false);
	addPon(Tile::TwoOfCircles, false);
	addChii(Tile::ThreeOfBamboos, false);
	addPon(Tile::ThreeOfBamboos, false);	

	s.setRon();
	w.calculate();

	CHECK(w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, AllTripletHand_ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addPon(Tile::OneOfCharacters, false);
	addPon(Tile::TwoOfCircles, false);
	addPon(Tile::ThreeOfBamboos, false);
	addPon(Tile::SevenOfCharacters, false);

	s.setRon();
	w.calculate();

	CHECK(w.hasHand(Hand::AllTripletHand));
	CHECK(w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, ThreeColourTriplets)
{
	addPair(Tile::WestWind);
	addPon(Tile::ThreeOfCharacters, false);
	addPon(Tile::ThreeOfCircles, false);
	addPon(Tile::ThreeOfBamboos, false);
	addChii(Tile::SevenOfCharacters, false);

	w.calculate();

	CHECK(w.hasHand(Hand::ThreeColourTriplets));
}

TEST(WiningHandCounterTest, ThreeKans)
{
	addPair(Tile::WestWind);
	addKan(Tile::ThreeOfCharacters, false);
	addKan(Tile::ThreeOfCircles, true);
	addKan(Tile::ThreeOfBamboos, true);
	addChii(Tile::SevenOfCharacters, false);

	w.calculate();

	CHECK(w.hasHand(Hand::ThreeKans));
}

TEST(WiningHandCounterTest, AllSimples)
{
	addPair(Tile::ThreeOfCharacters);
	addChii(Tile::FiveOfCharacters, false);
	addPon(Tile::ThreeOfCircles, false);
	addChii(Tile::ThreeOfBamboos, false);
	addChii(Tile::SixOfBamboos, false);

	w.calculate();

	CHECK(w.hasHand(Hand::AllSimples));
}

TEST(WiningHandCounterTest, HonorTiles_Dragon)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfBamboos, false);
	addPon(Tile::WhiteDragon, false);

	w.calculate();

	CHECK(w.hasHand(Hand::WhiteDragon));
}

TEST(WiningHandCounterTest, HonorTiles_Wind)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::SouthWind);

	addPair(Tile::WhiteDragon);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::TwoOfCircles, false);
	addChii(Tile::TwoOfBamboos, false);
	addPon(Tile::EastWind, false);

	w.calculate();

	CHECK(w.hasHand(Hand::EastWind));

	s.setOwnWind(Tile::EastWind);
	w.calculate();

	CHECK(w.hasHand(Hand::DoubleEastWind));

	s.setRountWind(Tile::SouthWind);
	w.calculate();

	CHECK(w.hasHand(Hand::EastWind));
}

TEST(WiningHandCounterTest, TerminalOrHonorInEachSet)
{
	addPair(Tile::WestWind);
	addPon(Tile::WhiteDragon, false);
	addPon(Tile::OneOfCharacters, false);
	addChii(Tile::OneOfCharacters, false);
	addChii(Tile::SevenOfBamboos, false);

	w.calculate();

	CHECK(w.hasHand(Hand::TerminalOrHonorInEachSet));
}

TEST(WiningHandCounterTest, AllTerminalsAndHornors_AllTripletHand)
{
	addPair(Tile::WestWind);
	addPon(Tile::NorthWind, true);
	addPon(Tile::OneOfCharacters, true);
	addPon(Tile::NineOfCircles, false);
	addPon(Tile::NineOfBamboos, false);

	w.calculate();

	CHECK(w.hasHand(Hand::AllTerminalsAndHornors));
	CHECK(w.hasHand(Hand::AllTripletHand));
}

TEST(WiningHandCounterTest, AllTerminalsAndHornors_SevenPairs)
{
	addPair(Tile::OneOfCharacters);
	addPair(Tile::NineOfCharacters);
	addPair(Tile::OneOfCircles);	
	addPair(Tile::NineOfCircles);
	addPair(Tile::NineOfBamboos);
	addPair(Tile::WhiteDragon);
	addPair(Tile::WestWind);

	w.calculate();

	CHECK(w.hasHand(Hand::AllTerminalsAndHornors));
	CHECK(w.hasHand(Hand::SevenPairs));
}

TEST(WiningHandCounterTest, TerminalInEachSet)
{
	addPair(Tile::NineOfCharacters);
	addChii(Tile::OneOfCharacters, false);
	addPon(Tile::NineOfCircles, false);
	addChii(Tile::OneOfBamboos, false);
	addChii(Tile::SevenOfBamboos, false);	

	w.calculate();

	CHECK(w.hasHand(Hand::TerminalInEachSet));
}

TEST(WiningHandCounterTest, LittleThreeDragons)
{
	addPair(Tile::WhiteDragon);
	addPon(Tile::RedDragon, false);
	addPon(Tile::GreenDragon, false);
	addChii(Tile::TwoOfCharacters, false);
	addChii(Tile::SixOfBamboos, false);

	w.calculate();

	CHECK(w.hasHand(Hand::LittleThreeDragons));
}

TEST(WiningHandCounterTest, HalfFlush)
{
	addPair(Tile::WestWind);
	addPon(Tile::EastWind, false);
	addChii(Tile::OneOfCharacters, false);
	addPon(Tile::FiveOfCharacters, false);
	addChii(Tile::SixOfCharacters, false);

	w.calculate();

	CHECK(w.hasHand(Hand::HalfFlush));
}

TEST(WiningHandCounterTest, Flush)
{
	addPair(Tile::OneOfCharacters);
	addPon(Tile::TwoOfCharacters, false);
	addPon(Tile::FourOfCharacters, false);
	addChii(Tile::SixOfCharacters, false);
	addChii(Tile::SevenOfCharacters, false);

	w.calculate();

	CHECK(w.hasHand(Hand::Flush));
}
