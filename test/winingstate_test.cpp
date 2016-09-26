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
#include "doubling-factor-report.h"
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

	void selfDrawn(SelfDrawnSituation situation = {})
	{
		auto tile = h.lastTile();
		s.selfDrawn(tile, situation);
	}

	void winByDiscard(WinByDiscardSituation situation = {})
	{
		auto tile = h.lastTile();
		s.winByDiscard(tile, situation);
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

	WinByDiscardSituation situation;
	situation.is_one_shot = true;

	winByDiscard(situation);
	w.compute();

	CHECK(w.hasPattern(Pattern::OneShot));
}

TEST(WiningStateTest, Not_OneShot_ReadyOnly)
{
	addNoWiningHand();

	SelfDrawnSituation situation;
	situation.is_one_shot = true;

	selfDrawn(situation);
	w.compute();

	CHECK(!w.hasPattern(Pattern::OneShot));
}

TEST(WiningStateTest, DeadWallDraw)
{
	addNoWiningHand();

	SelfDrawnSituation situation;
	situation.is_dead_wall = true;

	selfDrawn(situation);
	w.compute();

	CHECK(w.hasPattern(Pattern::DeadWallDraw));
}

TEST(WiningStateTest, RobbingQuad)
{
	addNoWiningHand();

	WinByDiscardSituation situation;
	situation.is_robbing_quad = true;

	winByDiscard(situation);
	w.compute();

	CHECK(w.hasPattern(Pattern::RobbingQuad));
}

TEST(WiningStateTest, LastTileFromTheWall)
{
	addNoWiningHand();

	SelfDrawnSituation situation;
	situation.is_last_wall = true;

	selfDrawn(situation);
	w.compute();

	CHECK(w.hasPattern(Pattern::LastTileFromTheWall));
}

TEST(WiningStateTest, LastDiscard)
{
	addNoWiningHand();

	WinByDiscardSituation situation;
	situation.is_last_discard = true;

	winByDiscard(situation);
	w.compute();

	CHECK(w.hasPattern(Pattern::LastDiscard));
}

TEST(WiningStateTest, DoubleReady)
{
	addNoWiningHand();

	s.doubleReady();
	winByDiscard();
	w.compute();

	CHECK(w.hasPattern(Pattern::DoubleReady));
}

TEST(WiningStateTest, BonusTiles)
{
	addPair(Tile::OneOfBamboos);
	addSequence(Tile::TwoOfBamboos);
	addSequence(Tile::ThreeOfCharacters);
	addTriplet(Tile::SixOfCircles);
	addSequence(Tile::SevenOfCharacters);

	s.addBonusTile(Tile::OneOfBamboos);
	s.addBonusTile(Tile::SixOfCircles);
	s.addBonusTile(Tile::NineOfCharacters);

	s.readyHand();
	selfDrawn();
	auto r = w.compute();

	CHECK(w.hasPattern(Pattern::SelfDrawn));
	CHECK_EQUAL(6, r.bonus_tile_count);
}

TEST(WiningStateTest, BonusTiles_RedFives)
{
	addPair(Tile::RedFiveOfBamboos);
	addSequence(Tile::FiveOfBamboos);
	addSequence(Tile::ThreeOfCharacters);
	addTriplet(Tile::SixOfCircles);
	addSequence(Tile::SevenOfCharacters);

	s.addBonusTile(Tile::FiveOfBamboos);

	s.readyHand();
	selfDrawn();
	auto r = w.compute();

	CHECK(w.hasPattern(Pattern::SelfDrawn));
	CHECK_EQUAL(5, r.bonus_tile_count);
}
