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

	s.readyHand();
	winByDiscard();
	w.compute();

	CHECK(w.hasPattern(Pattern::ReadyHand));
}

TEST(WiningStateTest, OneShot)
{
	addNoWiningHand();
	s.readyHand();

	s.setOneShot();
	winByDiscard();
	w.compute();

	CHECK(w.hasPattern(Pattern::OneShot));
}

TEST(WiningStateTest, Not_OneShot_ReadyOnly)
{
	addNoWiningHand();
	
	s.setOneShot();
	selfDrawn();
	w.compute();

	CHECK(!w.hasPattern(Pattern::OneShot));
}

TEST(WiningStateTest, DeadWallDraw)
{
	addNoWiningHand();

	s.setDeadWallDraw();
	selfDrawn();
	w.compute();

	CHECK(w.hasPattern(Pattern::DeadWallDraw));
}

TEST(WiningStateTest, RobbingQuad)
{
	addNoWiningHand();

	s.setRobbingQuad();
	winByDiscard();
	w.compute();

	CHECK(w.hasPattern(Pattern::RobbingQuad));
}

TEST(WiningStateTest, LastTileFromTheWall)
{
	addNoWiningHand();
	
	s.setLastTileFromTheWall();
	selfDrawn();
	w.compute();

	CHECK(w.hasPattern(Pattern::LastTileFromTheWall));
}

TEST(WiningStateTest, LastDiscard)
{
	addNoWiningHand();

	s.setLastDiscard();
	winByDiscard();
	w.compute();

	CHECK(w.hasPattern(Pattern::LastDiscard));
}

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
