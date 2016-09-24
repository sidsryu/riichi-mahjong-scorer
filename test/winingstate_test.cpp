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

TEST_GROUP(WiningStateTest)
{
	PlayerHand h;
	WiningState s;
	WiningHandCounter w { h, s };

	void addPair(Tile tile)
	{
		h.add(tile);
		h.add(tile);
	}

	void addTriplet(Tile tile)
	{
		h.add(tile);
		h.add(tile);
		h.add(tile);
	}

	void addSequence(Tile tile)
	{
		assert(int(tile) % 10 <= 7);

		h.add(tile);
		h.add(NextTile()(h.lastTile()));
		h.add(NextTile()(h.lastTile()));
	}

	void addNoWiningHand()
	{
		addPair(Tile::OneOfBamboos);

		addSequence(Tile::TwoOfBamboos);
		addSequence(Tile::ThreeOfCharacters);
		addTriplet(Tile::SixOfCircles);

		addSequence(Tile::SevenOfCharacters);
	}
};

TEST(WiningStateTest, NoHandClaim)
{
	addNoWiningHand();

	h.bindSequence({
		Tile::SevenOfCharacters,
		Tile::EightOfCharacters,
		Tile::NineOfCharacters
	});
	w.compute();

	CHECK(w.isNoHand());
}

TEST(WiningStateTest, NoHandRon)
{
	addNoWiningHand();

	s.setRon();
	w.compute();

	CHECK(w.isNoHand());
}

TEST(WiningStateTest, SelfPick)
{
	addNoWiningHand();

	s.setTsumo();
	w.compute();

	CHECK(w.hasHand(Hand::SelfPick));
}

TEST(WiningStateTest, ReadyHand)
{
	addNoWiningHand();

	s.setRiichi();
	s.setRon();
	w.compute();

	CHECK(w.hasHand(Hand::ReadyHand));
}

TEST(WiningStateTest, OneShot)
{}

TEST(WiningStateTest, DeadWallDraw)
{}

TEST(WiningStateTest, RobblingAQuad)
{}

TEST(WiningStateTest, LastTileFromTheWall)
{}

TEST(WiningStateTest, LastDiscard)
{}

TEST(WiningStateTest, Dora)
{}

TEST(WiningStateTest, DoubleReady)
{
	addNoWiningHand();

	s.setDoubleRiichi();
	s.setRon();
	w.compute();

	CHECK(w.hasHand(Hand::DoubleReady));
}
