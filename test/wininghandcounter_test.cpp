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

	void addNoWiningHand()
	{
		addPair(Tile::OneOfBamboos);

		addChii(Tile::TwoOfBamboos);		
		addChii(Tile::ThreeOfCharacters);
		addPon(Tile::SixOfCircles);

		addChii(Tile::SevenOfCharacters);
	}
};

TEST(WiningHandCounterTest, NoPointsHand)
{
	addPair(Tile::FiveOfCharacters);
	addChii(Tile::TwoOfBamboos);
	addChii(Tile::SevenOfBamboos);
	addChii(Tile::OneOfCircles);

	h.add(Tile::SixOfCircles);
	h.add(Tile::SevenOfCircles);
	h.add(Tile::EightOfCircles);

	w.calculate();

	CHECK(w.hasHand(Hand::NoPointsHand));
}

TEST(WiningHandCounterTest, OneSetOfIdenticalSequences)
{}

TEST(WiningHandCounterTest, HonorTiles)
{}

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

TEST(WiningHandCounterTest, SevenPairsFourSuit)
{
	addPair(Tile::EastWind);
	addPair(Tile::NorthWind);
	addPair(Tile::ThreeOfCharacters);
	addPair(Tile::NineOfCircles);
	addPair(Tile::OneOfBamboos);
	addPair(Tile::GreenDragon);
	addPair(Tile::GreenDragon);
	w.calculate();

	CHECK(w.hasHand(Hand::SevenPairs));
}
