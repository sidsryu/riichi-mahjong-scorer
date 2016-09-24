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

	void addTriplet(Tile tile, bool is_open)
	{
		h.add(tile);
		h.add(tile);
		h.add(tile);

		if (is_open)
		{
			h.bindTriplet({ tile, tile, tile });
		}
	}

	void addSequence(Tile tile, bool is_open)
	{
		auto next_tile = NextTile()(tile);
		auto last_tile = NextTile()(next_tile);

		h.add(tile);
		h.add(next_tile);
		h.add(last_tile);

		if (is_open)
		{
			h.bindSequence({ tile, next_tile, last_tile });
		}
	}

	void addQuad(Tile tile, bool is_open)
	{
		h.add(tile);
		h.add(tile);
		h.add(tile);
		h.add(tile);

		if (is_open)
		{
			h.bindOpenQuad({ tile,tile,tile,tile });
		}
		else
		{
			h.bindClosedQuad({ tile,tile,tile,tile });
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
	w.compute();

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
	w.compute();

	CHECK(!w.hasHand(Hand::SevenPairs));
}

TEST(WiningHandCounterTest, NoPointsHand)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	w.compute();

	CHECK(w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, Not_NoPointsHand_Open)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, true);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	w.compute();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, Not_NoPointsHand_NotMultiWait)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);

	h.add(Tile::NineOfCircles);
	h.add(Tile::EightOfCircles);
	h.add(Tile::SevenOfCircles);

	w.compute();

	CHECK(!w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, Not_NoPointsHand_DragonPair)
{
	addPair(Tile::WhiteDragon);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	w.compute();

	CHECK(!w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, NoPointsHand_ScoringWindPair)
{
	s.setRountWind(Tile::EastWind);

	addPair(Tile::EastWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	w.compute();

	CHECK(!w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, OneSetOfIdenticalSequences)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);
	addTriplet(Tile::NineOfBamboos, false);

	w.compute();

	CHECK(w.hasHand(Hand::OneSetOfIdenticalSequences));
}

TEST(WiningHandCounterTest, Not_OneSetOfIdenticalSequences_Open)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);
	addTriplet(Tile::NineOfBamboos, true);

	w.compute();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, ThreeColourStraights)
{
	addPair(Tile::WestWind);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, true);
	
	w.compute();

	CHECK(w.hasHand(Hand::ThreeColourStraights));
}

TEST(WiningHandCounterTest, Straight)
{
	addPair(Tile::WestWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::FourOfCharacters, false);
	addSequence(Tile::SevenOfCharacters, false);
	addTriplet(Tile::OneOfBamboos, false);

	w.compute();

	CHECK(w.hasHand(Hand::Straight));
}

TEST(WiningHandCounterTest, TwoSetsOfIdenticalSequences)
{
	addPair(Tile::WestWind);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::ThreeOfCircles, false);
	addSequence(Tile::ThreeOfCircles, false);

	w.compute();

	CHECK(w.hasHand(Hand::TwoSetsOfIdenticalSequences));
	CHECK(!w.hasHand(Hand::SevenPairs));
}

TEST(WiningHandCounterTest, Not_TwoSetsOfIdenticalSequences_Open)
{
	addPair(Tile::WestWind);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::ThreeOfCircles, false);
	addSequence(Tile::ThreeOfCircles, false);

	h.bindSequence({
		Tile::ThreeOfCircles,
		Tile::FourOfCircles,
		Tile::FiveOfCircles
	});

	w.compute();

	CHECK(!w.hasHand(Hand::TwoSetsOfIdenticalSequences));
}

TEST(WiningHandCounterTest, AllTripletHand)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, true);
	addTriplet(Tile::TwoOfCircles, true);
	addTriplet(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::SevenOfCharacters, false);
	
	w.compute();

	CHECK(w.hasHand(Hand::AllTripletHand));
}

TEST(WiningHandCounterTest, ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addTriplet(Tile::ThreeOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	w.compute();

	CHECK(w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, Not_ThreeClosedTriplets_Ron)
{
	addPair(Tile::WestWind);	
	addSequence(Tile::SevenOfCharacters, false);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);	
	addTriplet(Tile::ThreeOfBamboos, false);	

	s.setRon();
	w.compute();

	CHECK(!w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, ThreeClosedTriplets_Ron)
{
	addPair(Tile::WestWind);	
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addSequence(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::ThreeOfBamboos, false);	

	s.setRon();
	w.compute();

	CHECK(w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, AllTripletHand_ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addTriplet(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::SevenOfCharacters, false);

	s.setRon();
	w.compute();

	CHECK(w.hasHand(Hand::AllTripletHand));
	CHECK(w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, ThreeColourTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::ThreeOfCharacters, false);
	addTriplet(Tile::ThreeOfCircles, false);
	addTriplet(Tile::ThreeOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	w.compute();

	CHECK(w.hasHand(Hand::ThreeColourTriplets));
}

TEST(WiningHandCounterTest, ThreeQuads)
{
	addPair(Tile::WestWind);
	addQuad(Tile::ThreeOfCharacters, false);
	addQuad(Tile::ThreeOfCircles, true);
	addQuad(Tile::ThreeOfBamboos, true);
	addSequence(Tile::SevenOfCharacters, false);

	w.compute();

	CHECK(w.hasHand(Hand::ThreeQuads));
}

TEST(WiningHandCounterTest, AllSimples)
{
	addPair(Tile::ThreeOfCharacters);
	addSequence(Tile::FiveOfCharacters, false);
	addTriplet(Tile::ThreeOfCircles, false);
	addSequence(Tile::ThreeOfBamboos, false);
	addSequence(Tile::SixOfBamboos, false);

	w.compute();

	CHECK(w.hasHand(Hand::AllSimples));
}

TEST(WiningHandCounterTest, HonorTiles_Dragon)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addTriplet(Tile::WhiteDragon, false);

	w.compute();

	CHECK(w.hasHand(Hand::WhiteDragon));
}

TEST(WiningHandCounterTest, HonorTiles_Wind)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::SouthWind);

	addPair(Tile::WhiteDragon);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addTriplet(Tile::EastWind, false);

	w.compute();

	CHECK(w.hasHand(Hand::EastWind));

	s.setOwnWind(Tile::EastWind);
	w.compute();

	CHECK(w.hasHand(Hand::DoubleEastWind));

	s.setRountWind(Tile::SouthWind);
	w.compute();

	CHECK(w.hasHand(Hand::EastWind));
}

TEST(WiningHandCounterTest, TerminalOrHonorInEachSet)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::WhiteDragon, false);
	addTriplet(Tile::OneOfCharacters, false);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::SevenOfBamboos, false);

	w.compute();

	CHECK(w.hasHand(Hand::TerminalOrHonorInEachSet));
}

TEST(WiningHandCounterTest, AllTerminalsAndHornors_AllTripletHand)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::NorthWind, true);
	addTriplet(Tile::OneOfCharacters, true);
	addTriplet(Tile::NineOfCircles, false);
	addTriplet(Tile::NineOfBamboos, false);

	w.compute();

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

	w.compute();

	CHECK(w.hasHand(Hand::AllTerminalsAndHornors));
	CHECK(w.hasHand(Hand::SevenPairs));
}

TEST(WiningHandCounterTest, TerminalInEachSet)
{
	addPair(Tile::NineOfCharacters);
	addSequence(Tile::OneOfCharacters, false);
	addTriplet(Tile::NineOfCircles, false);
	addSequence(Tile::OneOfBamboos, false);
	addSequence(Tile::SevenOfBamboos, false);	

	w.compute();

	CHECK(w.hasHand(Hand::TerminalInEachSet));
}

TEST(WiningHandCounterTest, LittleThreeDragons)
{
	addPair(Tile::WhiteDragon);
	addTriplet(Tile::RedDragon, false);
	addTriplet(Tile::GreenDragon, false);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::SixOfBamboos, false);

	w.compute();

	CHECK(w.hasHand(Hand::LittleThreeDragons));
}

TEST(WiningHandCounterTest, HalfFlush)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::EastWind, false);
	addSequence(Tile::OneOfCharacters, false);
	addTriplet(Tile::FiveOfCharacters, false);
	addSequence(Tile::SixOfCharacters, false);

	w.compute();

	CHECK(w.hasHand(Hand::HalfFlush));
}

TEST(WiningHandCounterTest, Flush)
{
	addPair(Tile::OneOfCharacters);
	addTriplet(Tile::TwoOfCharacters, false);
	addTriplet(Tile::FourOfCharacters, false);
	addSequence(Tile::SixOfCharacters, false);
	addSequence(Tile::SevenOfCharacters, false);

	w.compute();

	CHECK(w.hasHand(Hand::Flush));
}
