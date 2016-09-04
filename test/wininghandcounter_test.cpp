#include "CppUTest/TestHarness.h"
#include "wining-hand-counter.h"
#include "player-hand.h"
#include "hand-define.h"
#include "tile-define.h"

TEST_GROUP(WiningHandCounterTest)
{
	PlayerHand h;
	WiningHandCounter w { h };

	void makeNoHandWait()
	{
		h.tsumo(Tile::OneOfBamboos);
		h.tsumo(Tile::OneOfBamboos);

		h.tsumo(Tile::TwoOfBamboos);
		h.tsumo(Tile::ThreeOfBamboos);
		h.tsumo(Tile::FourOfBamboos);

		h.tsumo(Tile::SixOfCircles);
		h.tsumo(Tile::SixOfCircles);
		h.tsumo(Tile::SixOfCircles);

		h.tsumo(Tile::ThreeOfCharacters);
		h.tsumo(Tile::FourOfCharacters);
		h.tsumo(Tile::FiveOfCharacters);

		h.tsumo(Tile::EightOfCharacters);
		h.tsumo(Tile::NineOfCharacters);
	}
};

TEST(WiningHandCounterTest, SelfPick)
{
	makeNoHandWait();
	h.tsumo(Tile::SevenOfCharacters);
	w.calculate();

	CHECK(w.hasHand(Hand::SelfPick));
}

TEST(WiningHandCounterTest, NoHandClaim)
{
	makeNoHandWait();
	h.tsumo(Tile::SevenOfCharacters);
	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, NoHandRon)
{
	makeNoHandWait();
	h.ron(Tile::SevenOfCharacters);
	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningHandCounterTest, ReadyHand)
{}

TEST(WiningHandCounterTest, OneShot)
{}

TEST(WiningHandCounterTest, NoPointsHand)
{}

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
