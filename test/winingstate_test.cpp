#include "CppUTest/TestHarness.h"
#include "wining-hand-counter.h"
#include "wining-state.h"
#include "player-hand.h"
#include "tile-functor.h"
#include "hand-define.h"
#include "tile-define.h"
#include "type-define.h"
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

TEST(WiningStateTest, NoHandClaim)
{
	addNoWiningHand();

	h.bindChii({
		Tile::SevenOfCharacters,
		Tile::EightOfCharacters,
		Tile::NineOfCharacters
	});
	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningStateTest, NoHandRon)
{
	addNoWiningHand();

	s.setRon();
	w.calculate();

	CHECK(w.isNoHand());
}

TEST(WiningStateTest, SelfPick)
{
	addNoWiningHand();

	s.setTsumo();
	w.calculate();

	CHECK(w.hasHand(Hand::SelfPick));
}

TEST(WiningStateTest, ReadyHand)
{
	addNoWiningHand();

	s.setRiichi();
	s.setRon();
	w.calculate();

	CHECK(w.hasHand(Hand::ReadyHand));
}

TEST(WiningStateTest, OneShot)
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
	w.calculate();

	CHECK(w.hasHand(Hand::DoubleReady));
}
