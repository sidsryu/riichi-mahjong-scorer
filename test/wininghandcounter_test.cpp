#include "CppUTest/TestHarness.h"
#include "wining-hand-counter.h"
#include "player-hand.h"
#include "hand-define.h"
#include "tile-define.h"
#include <cassert>

TEST_GROUP(WiningHandCounterTest)
{
	PlayerHand h;
	WiningHandCounter w { h };

	void tsumoPair(Tile tile)
	{
		h.tsumo(tile);
		h.tsumo(tile);
	}

	void tsumoPon(Tile tile)
	{
		h.tsumo(tile);
		h.tsumo(tile);
		h.tsumo(tile);
	}

	void tsumoChii(Tile tile)
	{
		assert(int(tile) % 10 <= 7);

		h.tsumo(tile);
		h.tsumo(static_cast<Tile>(int(tile) + 1));
		h.tsumo(static_cast<Tile>(int(tile) + 2));
	}

	void waitNoWiningHand()
	{
		tsumoPair(Tile::OneOfBamboos);

		tsumoChii(Tile::TwoOfBamboos);		
		tsumoChii(Tile::ThreeOfCharacters);
		tsumoPon(Tile::SixOfCircles);
		
		h.tsumo(Tile::EightOfCharacters);
		h.tsumo(Tile::NineOfCharacters);
	}
};

TEST(WiningHandCounterTest, SelfPick)
{
	waitNoWiningHand();
	h.tsumo(Tile::SevenOfCharacters);
	w.calculate();

	CHECK(w.hasHand(Hand::SelfPick));
}

TEST(WiningHandCounterTest, NoHandClaim)
{
	waitNoWiningHand();
	h.chii(Tile::SevenOfCharacters);
	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, NoHandRon)
{
	waitNoWiningHand();
	h.ron(Tile::SevenOfCharacters);
	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, ReadyHand)
{
	waitNoWiningHand();
	h.riichi();
	h.ron(Tile::SevenOfCharacters);	
	w.calculate();

	CHECK(w.hasHand(Hand::ReadyHand));
}

TEST(WiningHandCounterTest, OneShot)
{}

TEST(WiningHandCounterTest, NoPointsHand)
{
	tsumoPair(Tile::FiveOfCharacters);
	tsumoChii(Tile::TwoOfBamboos);
	tsumoChii(Tile::SevenOfBamboos);
	tsumoChii(Tile::OneOfCircles);

	h.tsumo(Tile::SixOfCircles);
	h.tsumo(Tile::SevenOfCircles);
	h.tsumo(Tile::EightOfCircles);

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

TEST(WiningHandCounterTest, LastTileFromTheWall)
{}

TEST(WiningHandCounterTest, LastDiscard)
{}

TEST(WiningHandCounterTest, Dora)
{}

TEST(WiningHandCounterTest, DoubleReady)
{
	waitNoWiningHand();
	h.doubleRiichi();
	h.ron(Tile::SevenOfCharacters);
	w.calculate();

	CHECK(w.hasHand(Hand::DoubleReady));
}

TEST(WiningHandCounterTest, SevenPairs)
{
	tsumoPair(Tile::EastWind);
	tsumoPair(Tile::NorthWind);
	tsumoPair(Tile::ThreeOfCharacters);
	tsumoPair(Tile::NineOfCircles);
	tsumoPair(Tile::OneOfBamboos);
	tsumoPair(Tile::GreenDragon);
	tsumoPair(Tile::OneOfCharacters);	
	w.calculate();

	CHECK(w.hasHand(Hand::SevenPairs));
}

TEST(WiningHandCounterTest, SevenPairsFourSuit)
{
	tsumoPair(Tile::EastWind);
	tsumoPair(Tile::NorthWind);
	tsumoPair(Tile::ThreeOfCharacters);
	tsumoPair(Tile::NineOfCircles);
	tsumoPair(Tile::OneOfBamboos);
	tsumoPair(Tile::GreenDragon);
	tsumoPair(Tile::GreenDragon);
	w.calculate();

	CHECK(w.hasHand(Hand::SevenPairs));
}
