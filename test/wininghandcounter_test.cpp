#include "CppUTest/TestHarness.h"
#include "wining-hand-counter.h"
#include "wining-state.h"
#include "player-hand.h"
#include "tile-functor.h"
#include "hand-define.h"
#include "tile-define.h"
#include "type-define.h"
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

	void addPon(Tile tile)
	{
		h.add(tile);
		h.add(tile);
		h.add(tile);
	}

	void addChii(Tile tile)
	{
		assert(int(tile) % 10 <= 7);

		h.add(tile);
		h.add(NextTile()(h.lastTile()));
		h.add(NextTile()(h.lastTile()));
	}

	void addKanAndBind(Tile tile)
	{
		h.add(tile);
		h.add(tile);
		h.add(tile);
		h.add(tile);

		h.bindKan({
			tile,
			tile,
			tile,
			tile
		});
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
	addChii(Tile::OneOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfBamboos);
	addChii(Tile::SevenOfCharacters);

	w.calculate();

	CHECK(w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, Not_NoPointsHand_Open)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfBamboos);
	addChii(Tile::SevenOfCharacters);
	
	h.bindChii({
		Tile::OneOfCharacters,
		Tile::TwoOfCharacters,
		Tile::ThreeOfCharacters
	});

	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, Not_NoPointsHand_NotMultiWait)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfBamboos);
		
	h.add(Tile::NineOfCircles);
	h.add(Tile::EightOfCircles);
	h.add(Tile::SevenOfCircles);

	w.calculate();

	CHECK(!w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, Not_NoPointsHand_DragonPair)
{
	addPair(Tile::WhiteDragon);
	addChii(Tile::OneOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfBamboos);
	addChii(Tile::SevenOfCharacters);

	w.calculate();

	CHECK(!w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, NoPointsHand_ScoringWindPair)
{
	s.setRountWind(Tile::EastWind);

	addPair(Tile::EastWind);
	addChii(Tile::OneOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfBamboos);
	addChii(Tile::SevenOfCharacters);

	w.calculate();

	CHECK(!w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, OneSetOfIdenticalSequences)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfCircles);
	addPon(Tile::NineOfBamboos);

	w.calculate();

	CHECK(w.hasHand(Hand::OneSetOfIdenticalSequences));
}

TEST(WiningHandCounterTest, Not_OneSetOfIdenticalSequences_Open)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfCircles);
	addPon(Tile::NineOfBamboos);

	h.bindPon({
		Tile::NineOfBamboos,
		Tile::NineOfBamboos,
		Tile::NineOfBamboos
	});

	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, ThreeColourStraights)
{
	addPair(Tile::WestWind);
	addChii(Tile::TwoOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfBamboos);
	addChii(Tile::SevenOfCharacters);
	
	h.bindChii({
		Tile::SevenOfCharacters,
		Tile::EightOfCharacters,
		Tile::NineOfCharacters
	});

	w.calculate();

	CHECK(w.hasHand(Hand::ThreeColourStraights));
}

TEST(WiningHandCounterTest, Straight)
{
	addPair(Tile::WestWind);
	addChii(Tile::OneOfCharacters);
	addChii(Tile::FourOfCharacters);
	addChii(Tile::SevenOfCharacters);
	addPon(Tile::OneOfBamboos);

	w.calculate();

	CHECK(w.hasHand(Hand::Straight));
}

TEST(WiningHandCounterTest, TwoSetsOfIdenticalSequences)
{
	addPair(Tile::WestWind);
	addChii(Tile::TwoOfCharacters);
	addChii(Tile::TwoOfCharacters);
	addChii(Tile::ThreeOfCircles);
	addChii(Tile::ThreeOfCircles);

	w.calculate();

	CHECK(w.hasHand(Hand::TwoSetsOfIdenticalSequences));
	CHECK(!w.hasHand(Hand::SevenPairs));
}

TEST(WiningHandCounterTest, Not_TwoSetsOfIdenticalSequences_Open)
{
	addPair(Tile::WestWind);
	addChii(Tile::TwoOfCharacters);
	addChii(Tile::TwoOfCharacters);
	addChii(Tile::ThreeOfCircles);
	addChii(Tile::ThreeOfCircles);

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
	addPon(Tile::OneOfCharacters);
	addPon(Tile::TwoOfCircles);
	addPon(Tile::ThreeOfBamboos);
	addPon(Tile::SevenOfCharacters);

	h.bindPon({
		Tile::OneOfCharacters,
		Tile::OneOfCharacters,
		Tile::OneOfCharacters
	});
	h.bindPon({
		Tile::TwoOfCircles,
		Tile::TwoOfCircles,
		Tile::TwoOfCircles
	});

	w.calculate();

	CHECK(w.hasHand(Hand::AllTripletHand));
}

TEST(WiningHandCounterTest, ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addPon(Tile::OneOfCharacters);
	addPon(Tile::TwoOfCircles);
	addPon(Tile::ThreeOfBamboos);
	addChii(Tile::SevenOfCharacters);

	w.calculate();

	CHECK(w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, Not_ThreeClosedTriplets_Ron)
{
	addPair(Tile::WestWind);	
	addChii(Tile::SevenOfCharacters);
	addPon(Tile::OneOfCharacters);
	addPon(Tile::TwoOfCircles);	
	addPon(Tile::ThreeOfBamboos);	

	s.setRon();
	w.calculate();

	CHECK(!w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, ThreeClosedTriplets_Ron)
{
	addPair(Tile::WestWind);	
	addPon(Tile::OneOfCharacters);
	addPon(Tile::TwoOfCircles);
	addChii(Tile::ThreeOfBamboos);
	addPon(Tile::ThreeOfBamboos);	
	
	s.setRon();
	w.calculate();

	CHECK(w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, AllTripletHand_ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addPon(Tile::OneOfCharacters);
	addPon(Tile::TwoOfCircles);
	addPon(Tile::ThreeOfBamboos);
	addPon(Tile::SevenOfCharacters);

	s.setRon();
	w.calculate();

	CHECK(w.hasHand(Hand::AllTripletHand));
	CHECK(w.hasHand(Hand::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, ThreeColourTriplets)
{
	addPair(Tile::WestWind);
	addPon(Tile::ThreeOfCharacters);
	addPon(Tile::ThreeOfCircles);
	addPon(Tile::ThreeOfBamboos);
	addChii(Tile::SevenOfCharacters);

	w.calculate();

	CHECK(w.hasHand(Hand::ThreeColourTriplets));
}

TEST(WiningHandCounterTest, ThreeKans)
{
	addPair(Tile::WestWind);
	addKanAndBind(Tile::ThreeOfCharacters);
	addKanAndBind(Tile::ThreeOfCircles);
	addKanAndBind(Tile::ThreeOfBamboos);
	addChii(Tile::SevenOfCharacters);

	w.calculate();

	CHECK(w.hasHand(Hand::ThreeKans));
}

TEST(WiningHandCounterTest, AllSimples)
{
	addPair(Tile::ThreeOfCharacters);
	addChii(Tile::FiveOfCharacters);
	addPon(Tile::ThreeOfCircles);
	addChii(Tile::ThreeOfBamboos);
	addChii(Tile::SixOfBamboos);

	w.calculate();

	CHECK(w.hasHand(Hand::AllSimples));
}

TEST(WiningHandCounterTest, HonorTiles_Dragon)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfBamboos);
	addPon(Tile::WhiteDragon);

	w.calculate();

	CHECK(w.hasHand(Hand::WhiteDragon));
}

TEST(WiningHandCounterTest, HonorTiles_Wind)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::SouthWind);

	addPair(Tile::WhiteDragon);
	addChii(Tile::OneOfCharacters);
	addChii(Tile::TwoOfCircles);
	addChii(Tile::TwoOfBamboos);
	addPon(Tile::EastWind);

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
}

TEST(WiningHandCounterTest, TerminalInEachSet)
{
}

TEST(WiningHandCounterTest, AllTerminalsAndHornors)
{
}

TEST(WiningHandCounterTest, LittleThreeDragons)
{
}

TEST(WiningHandCounterTest, HalfFlush)
{
}

TEST(WiningHandCounterTest, Flush)
{
}
