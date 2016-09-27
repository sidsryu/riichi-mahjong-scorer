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
	auto r = w.compute();

	CHECK(r.patterns.empty());
}

TEST(WiningStateTest, NoHandWinByDiscard)
{
	addNoWiningHand();

	winByDiscard();
	auto r= w.compute();

	CHECK(r.patterns.empty());
}

TEST(WiningStateTest, SelfDrawn)
{
	addNoWiningHand();

	selfDrawn();
	auto r = w.compute();

	CHECK_EQUAL(1, r.patterns.count(Pattern::SelfDrawn));
}

TEST(WiningStateTest, ReadyHand)
{
	addNoWiningHand();

	s.readyHand();
	winByDiscard();
	auto r = w.compute();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ReadyHand));
}

TEST(WiningStateTest, OneShot)
{
	addNoWiningHand();
	s.readyHand();

	WinByDiscardSituation situation;
	situation.is_one_shot = true;

	winByDiscard(situation);
	auto r = w.compute();

	CHECK_EQUAL(1, r.patterns.count(Pattern::OneShot));
}

TEST(WiningStateTest, Not_OneShot_ReadyOnly)
{
	addNoWiningHand();

	SelfDrawnSituation situation;
	situation.is_one_shot = true;

	selfDrawn(situation);
	auto r = w.compute();

	CHECK_EQUAL(0, r.patterns.count(Pattern::OneShot));
}

TEST(WiningStateTest, DeadWallDraw)
{
	addNoWiningHand();

	SelfDrawnSituation situation;
	situation.is_dead_wall = true;

	selfDrawn(situation);
	auto r = w.compute();

	CHECK_EQUAL(1, r.patterns.count(Pattern::DeadWallDraw));
}

TEST(WiningStateTest, RobbingQuad)
{
	addNoWiningHand();

	WinByDiscardSituation situation;
	situation.is_robbing_quad = true;

	winByDiscard(situation);
	auto r = w.compute();

	CHECK_EQUAL(1, r.patterns.count(Pattern::RobbingQuad));
}

TEST(WiningStateTest, LastTileFromTheWall)
{
	addNoWiningHand();

	SelfDrawnSituation situation;
	situation.is_last_wall = true;

	selfDrawn(situation);
	auto r = w.compute();

	CHECK_EQUAL(1, r.patterns.count(Pattern::LastTileFromTheWall));
}

TEST(WiningStateTest, LastDiscard)
{
	addNoWiningHand();

	WinByDiscardSituation situation;
	situation.is_last_discard = true;

	winByDiscard(situation);
	auto r = w.compute();

	CHECK_EQUAL(1, r.patterns.count(Pattern::LastDiscard));
}

TEST(WiningStateTest, DoubleReady)
{
	addNoWiningHand();

	s.doubleReady();
	winByDiscard();
	auto r = w.compute();

	CHECK_EQUAL(1, r.patterns.count(Pattern::DoubleReady));
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

	CHECK_EQUAL(1, r.patterns.count(Pattern::SelfDrawn));
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

	CHECK_EQUAL(1, r.patterns.count(Pattern::SelfDrawn));
	CHECK_EQUAL(5, r.bonus_tile_count);
}
