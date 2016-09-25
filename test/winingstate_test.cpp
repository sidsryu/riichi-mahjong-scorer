#include "CppUTest/TestHarness.h"
#include "wining-hand-counter.h"
#include "wining-state.h"
#include "player-hand.h"
#include "tile-functor.h"
#include "pattern-define.h"
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

	void selfDrawn()
	{
		auto tile = h.lastTile();
		s.selfDrawn(tile);
	}

	void winByDiscard()
	{
		auto tile = h.lastTile();
		s.winByDiscard(tile);
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
	s.claim();

	selfDrawn();
	w.compute();

	CHECK(w.isPattenEmpty());
}

TEST(WiningStateTest, NoHandWinByDiscard)
{
	addNoWiningHand();
		
	winByDiscard();
	w.compute();

	CHECK(w.isPattenEmpty());
}

TEST(WiningStateTest, SelfDrawn)
{
	addNoWiningHand();

	selfDrawn();
	w.compute();

	CHECK(w.hasPattern(Pattern::SelfDrawn));
}

TEST(WiningStateTest, ReadyHand)
{
	addNoWiningHand();

	s.ready();
	winByDiscard();
	w.compute();

	CHECK(w.hasPattern(Pattern::ReadyHand));
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

	s.doubleReady();	
	winByDiscard();
	w.compute();

	CHECK(w.hasPattern(Pattern::DoubleReady));
}
