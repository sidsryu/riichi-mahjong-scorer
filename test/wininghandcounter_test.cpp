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
};

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

	CHECK(!w.hasHand(Hand::OneSetOfIdenticalSequences));
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

	h.bindPon({
		Tile::WhiteDragon,
		Tile::WhiteDragon,
		Tile::WhiteDragon
	});

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

	h.bindPon({
		Tile::EastWind,
		Tile::EastWind,
		Tile::EastWind
	});

	w.calculate();

	CHECK(w.hasHand(Hand::EastWind));

	s.setOwnWind(Tile::EastWind);
	w.calculate();

	CHECK(w.hasHand(Hand::DoubleEastWind));

	s.setRountWind(Tile::SouthWind);
	w.calculate();

	CHECK(w.hasHand(Hand::EastWind));
}

TEST(WiningHandCounterTest, AllSimples)
{}

TEST(WiningHandCounterTest, DeadWallDraw)
{}

TEST(WiningHandCounterTest, RobblingAQuad)
{}

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
