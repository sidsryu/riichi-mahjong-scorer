#include "CppUTest/TestHarness.h"
#include "doubling-factor-counter.h"
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

using namespace mahjong;

TEST_GROUP(WiningStateTest)
{
	PlayerHand h;
	WiningState s;
	DoubligFactorCounter c { h, s };

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

	void addNoWiningHand(bool is_claim = false)
	{
		addPair(Tile::OneOfBamboos);

		addSequence(Tile::TwoOfBamboos);
		addSequence(Tile::ThreeOfCharacters);

		if (is_claim)
		{
			addTriplet(Tile::SixOfCircles);
			h.bindTriplet({
				Tile::SixOfCircles,
				Tile::SixOfCircles,
				Tile::SixOfCircles
			});
		}

		addSequence(Tile::SevenOfCharacters);
	}

	void selfDrawn(SelfDrawnSituation situation = {})
	{
		s.selfDrawn(situation);
	}

	void winByDiscard(WinByDiscardSituation situation = {})
	{
		s.winByDiscard(situation);
	}
};

TEST(WiningStateTest, NoHandClaim)
{
	addNoWiningHand(true);

	selfDrawn();
	auto r = c.report();

	CHECK(r.patterns.empty());
	CHECK_EQUAL(0, r.doubling_factor);
}

TEST(WiningStateTest, NoHandWinByDiscard)
{
	addNoWiningHand();

	winByDiscard();
	auto r= c.report();

	CHECK(r.patterns.empty());
	CHECK_EQUAL(0, r.doubling_factor);
}

TEST(WiningStateTest, SelfDrawn)
{
	addNoWiningHand();

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::SelfDrawn));
	CHECK_EQUAL(1, r.doubling_factor);
}

TEST(WiningStateTest, ReadyHand)
{
	addNoWiningHand();

	h.readyHand();	
	winByDiscard();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ReadyHand));
	CHECK_EQUAL(1, r.doubling_factor);
}

TEST(WiningStateTest, OneShot)
{
	addNoWiningHand();
	h.readyHand();

	WinByDiscardSituation situation;
	situation.is_one_shot = true;

	winByDiscard(situation);
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ReadyHand));
	CHECK_EQUAL(1, r.patterns.count(Pattern::OneShot));
	CHECK_EQUAL(2, r.doubling_factor);
}

TEST(WiningStateTest, Not_OneShot_ReadyOnly)
{
	addNoWiningHand();

	SelfDrawnSituation situation;
	situation.is_one_shot = true;

	selfDrawn(situation);
	auto r = c.report();

	CHECK_EQUAL(0, r.patterns.count(Pattern::OneShot));
}

TEST(WiningStateTest, DeadWallDraw)
{
	addNoWiningHand(true);

	SelfDrawnSituation situation;
	situation.is_dead_wall = true;

	selfDrawn(situation);
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::DeadWallDraw));
	CHECK_EQUAL(1, r.doubling_factor);
}

TEST(WiningStateTest, RobbingQuad)
{
	addNoWiningHand();

	WinByDiscardSituation situation;
	situation.is_robbing_quad = true;

	winByDiscard(situation);
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::RobbingQuad));
	CHECK_EQUAL(1, r.doubling_factor);
}

TEST(WiningStateTest, LastTileFromTheWall)
{
	addNoWiningHand(true);

	SelfDrawnSituation situation;
	situation.is_last_wall = true;

	selfDrawn(situation);
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::LastTileFromTheWall));
	CHECK_EQUAL(1, r.doubling_factor);
}

TEST(WiningStateTest, LastDiscard)
{
	addNoWiningHand();

	WinByDiscardSituation situation;
	situation.is_last_discard = true;

	winByDiscard(situation);
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::LastDiscard));
	CHECK_EQUAL(1, r.doubling_factor);
}

TEST(WiningStateTest, DoubleReady)
{
	addNoWiningHand();

	h.doubleReady();
	winByDiscard();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::DoubleReady));
	CHECK_EQUAL(2, r.doubling_factor);
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

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::SelfDrawn));
	CHECK_EQUAL(6, r.bonus_tile_count);
	CHECK_EQUAL(7, r.doubling_factor);
}

TEST(WiningStateTest, BonusTiles_Multiple)
{
	addPair(Tile::OneOfBamboos);
	addSequence(Tile::TwoOfBamboos);
	addSequence(Tile::ThreeOfCharacters);
	addTriplet(Tile::SixOfCircles);
	addSequence(Tile::SevenOfCharacters);

	s.addBonusTile(Tile::OneOfBamboos);	
	s.addBonusTile(Tile::OneOfBamboos);
	s.addBonusTile(Tile::OneOfBamboos);
	s.addBonusTile(Tile::OneOfBamboos);	
	
	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::SelfDrawn));
	CHECK_EQUAL(8, r.bonus_tile_count);
	CHECK_EQUAL(9, r.doubling_factor);
}

TEST(WiningStateTest, BonusTiles_RedFives)
{
	addPair(Tile::RedFiveOfBamboos);
	addSequence(Tile::FiveOfBamboos);
	addSequence(Tile::ThreeOfCharacters);
	addTriplet(Tile::SixOfCircles);
	addSequence(Tile::SevenOfCharacters);

	s.addBonusTile(Tile::FiveOfBamboos);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::SelfDrawn));
	CHECK_EQUAL(5, r.bonus_tile_count);
	CHECK_EQUAL(6, r.doubling_factor);
}

TEST(WiningStateTest, HeavenlyHand)
{
	addNoWiningHand();
		
	SelfDrawnSituation situation;
	situation.is_uninterrupted_first_drawn = true;

	selfDrawn(situation);
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::HeavenlyHand));
	CHECK_EQUAL(100, r.doubling_factor);
}

TEST(WiningStateTest, EarthlyHand)
{
	s.setSeatWind(Tile::SouthWind);

	addNoWiningHand();

	SelfDrawnSituation situation;
	situation.is_uninterrupted_first_drawn = true;

	selfDrawn(situation);
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::EarthlyHand));
	CHECK_EQUAL(100, r.doubling_factor);
}
