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

TEST_GROUP(DoublingFactorCounterTest)
{
	PlayerHand h;
	WiningState s;
	DoubligFactorCounter c { h, s };

	void addPair(Tile tile)
	{
		h.add(tile);
		h.add(tile);
	}

	void addTriplet(Tile tile, bool is_open)
	{
		h.add(tile);
		h.add(tile);
		h.add(tile);

		if (is_open)
		{
			h.bindTriplet({ tile, tile, tile });
			s.claim();
		}
	}

	void addSequence(Tile tile, bool is_open)
	{
		auto next_tile = NextTile()(tile);
		auto last_tile = NextTile()(next_tile);

		h.add(tile);
		h.add(next_tile);
		h.add(last_tile);

		if (is_open)
		{
			h.bindSequence({ tile, next_tile, last_tile });
			s.claim();
		}
	}

	void addQuad(Tile tile, bool is_open)
	{
		h.add(tile);
		h.add(tile);
		h.add(tile);
		h.add(tile);

		if (is_open)
		{
			h.bindOpenQuad({ tile,tile,tile,tile });
			s.claim();
		}
		else
		{
			h.bindClosedQuad({ tile,tile,tile,tile });
		}
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

TEST(DoublingFactorCounterTest, SevenPairs)
{
	addPair(Tile::EastWind);
	addPair(Tile::NorthWind);
	addPair(Tile::ThreeOfCharacters);
	addPair(Tile::NineOfCircles);
	addPair(Tile::OneOfBamboos);
	addPair(Tile::GreenDragon);
	addPair(Tile::OneOfCharacters);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::SevenPairs));
}

TEST(DoublingFactorCounterTest, Not_SevenPairs_FourSuit)
{
	addPair(Tile::EastWind);
	addPair(Tile::NorthWind);
	addPair(Tile::ThreeOfCharacters);
	addPair(Tile::NineOfCircles);
	addPair(Tile::OneOfBamboos);
	addPair(Tile::GreenDragon);
	addPair(Tile::GreenDragon);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(0, r.patterns.count(Pattern::SevenPairs));
}

TEST(DoublingFactorCounterTest, NoPointsHand)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::NoPointsHand));
}

TEST(DoublingFactorCounterTest, Not_NoPointsHand_Open)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, true);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK(r.patterns.empty());
}

TEST(DoublingFactorCounterTest, Not_NoPointsHand_NotMultiWait)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);

	h.add(Tile::NineOfCircles);
	h.add(Tile::EightOfCircles);
	h.add(Tile::SevenOfCircles);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(0, r.patterns.count(Pattern::NoPointsHand));
}

TEST(DoublingFactorCounterTest, Not_NoPointsHand_DragonPair)
{
	addPair(Tile::WhiteDragon);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(0, r.patterns.count(Pattern::NoPointsHand));
}

TEST(DoublingFactorCounterTest, NoPointsHand_ScoringWindPair)
{
	s.setRountWind(Tile::EastWind);

	addPair(Tile::EastWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(0, r.patterns.count(Pattern::NoPointsHand));
}

TEST(DoublingFactorCounterTest, OneSetOfIdenticalSequences)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);
	addTriplet(Tile::NineOfBamboos, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::OneSetOfIdenticalSequences));
}

TEST(DoublingFactorCounterTest, Not_OneSetOfIdenticalSequences_Open)
{
	addPair(Tile::SouthWind);	
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);	
	addTriplet(Tile::NineOfBamboos, true);

	selfDrawn();
	auto r = c.report();

	CHECK(r.patterns.empty());
}

TEST(DoublingFactorCounterTest, Not_OneSetOfIdenticalSequences_ThreeClosedTriplets)
{
	addPair(Tile::SouthWind);	
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);	
	addTriplet(Tile::NineOfBamboos, false);

	winByDiscard();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ThreeClosedTriplets));
}

TEST(DoublingFactorCounterTest, ThreeColourStraights)
{
	addPair(Tile::WestWind);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, true);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ThreeColourStraights));
}

TEST(DoublingFactorCounterTest, Straight)
{
	addPair(Tile::WestWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::FourOfCharacters, false);
	addSequence(Tile::SevenOfCharacters, false);
	addTriplet(Tile::OneOfBamboos, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::Straight));
}

TEST(DoublingFactorCounterTest, TwoSetsOfIdenticalSequences)
{
	addPair(Tile::WestWind);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::ThreeOfCircles, false);
	addSequence(Tile::ThreeOfCircles, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::TwoSetsOfIdenticalSequences));
	CHECK_EQUAL(0, r.patterns.count(Pattern::SevenPairs));
}

TEST(DoublingFactorCounterTest, TwoSetsOfIdenticalSequences_SameFourSequences)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::TwoSetsOfIdenticalSequences));
}

TEST(DoublingFactorCounterTest, Not_TwoSetsOfIdenticalSequences_Open)
{
	addPair(Tile::WestWind);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::ThreeOfCircles, false);
	addSequence(Tile::ThreeOfCircles, true);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(0, r.patterns.count(Pattern::TwoSetsOfIdenticalSequences));
}

TEST(DoublingFactorCounterTest, AllTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, true);
	addTriplet(Tile::TwoOfCircles, true);
	addTriplet(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::AllTriplets));
}

TEST(DoublingFactorCounterTest, ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addQuad(Tile::ThreeOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ThreeClosedTriplets));
}

TEST(DoublingFactorCounterTest, Not_ThreeClosedTriplets_WinByDiscard)
{
	addPair(Tile::WestWind);
	addSequence(Tile::SevenOfCharacters, false);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addTriplet(Tile::ThreeOfBamboos, false);
		
	winByDiscard();
	auto r = c.report();

	CHECK_EQUAL(0, r.patterns.count(Pattern::ThreeClosedTriplets));
}

TEST(DoublingFactorCounterTest, ThreeClosedTriplets_WinByDiscard)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addSequence(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::ThreeOfBamboos, false);

	winByDiscard();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ThreeClosedTriplets));
}

TEST(DoublingFactorCounterTest, AllTriplets_ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addTriplet(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::SevenOfCharacters, false);

	winByDiscard();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::AllTriplets));
	CHECK_EQUAL(1, r.patterns.count(Pattern::ThreeClosedTriplets));
}

TEST(DoublingFactorCounterTest, ThreeColourTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::ThreeOfCharacters, false);
	addTriplet(Tile::ThreeOfCircles, false);
	addQuad(Tile::ThreeOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ThreeColourTriplets));
}

TEST(DoublingFactorCounterTest, ThreeQuads)
{
	addPair(Tile::WestWind);
	addQuad(Tile::ThreeOfCharacters, false);
	addQuad(Tile::FourOfCircles, true);
	addQuad(Tile::FiveOfBamboos, true);
	addSequence(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ThreeQuads));
}

TEST(DoublingFactorCounterTest, ThreeQuads_ThreeClosedTriplets_AllTriplets)
{
	addPair(Tile::WestWind);
	addQuad(Tile::ThreeOfCharacters, false);
	addQuad(Tile::FourOfCircles, false);
	addQuad(Tile::FiveOfBamboos, false);
	addTriplet(Tile::SevenOfCharacters, true);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ThreeQuads));
	CHECK_EQUAL(1, r.patterns.count(Pattern::ThreeClosedTriplets));
	CHECK_EQUAL(1, r.patterns.count(Pattern::AllTriplets));
}

TEST(DoublingFactorCounterTest, AllSimples)
{
	addPair(Tile::ThreeOfCharacters);
	addSequence(Tile::FiveOfCharacters, false);
	addTriplet(Tile::ThreeOfCircles, false);
	addSequence(Tile::ThreeOfBamboos, false);
	addSequence(Tile::SixOfBamboos, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::AllSimples));
}

TEST(DoublingFactorCounterTest, HonorTiles_Dragon)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addTriplet(Tile::WhiteDragon, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::WhiteDragon));
}

TEST(DoublingFactorCounterTest, HonorTiles_Wind)
{
	s.setRountWind(Tile::EastWind);
	s.setSeatWind(Tile::SouthWind);

	addPair(Tile::WhiteDragon);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addTriplet(Tile::EastWind, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::EastWind));

	s.setSeatWind(Tile::EastWind);	
	r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::DoubleEastWind));

	s.setRountWind(Tile::SouthWind);
	r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::EastWind));
}

TEST(DoublingFactorCounterTest, TerminalOrHonorInEachSet)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::WhiteDragon, false);
	addTriplet(Tile::OneOfCharacters, false);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::SevenOfBamboos, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::TerminalOrHonorInEachSet));
}

TEST(DoublingFactorCounterTest, AllTerminalsAndHornors_AllTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::NorthWind, true);
	addTriplet(Tile::OneOfCharacters, true);
	addTriplet(Tile::NineOfCircles, false);
	addTriplet(Tile::NineOfBamboos, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::AllTerminalsAndHornors));
	CHECK_EQUAL(1, r.patterns.count(Pattern::AllTriplets));
	CHECK_EQUAL(0, r.patterns.count(Pattern::TerminalOrHonorInEachSet));
}

TEST(DoublingFactorCounterTest, AllTerminalsAndHornors_SevenPairs)
{
	addPair(Tile::OneOfCharacters);
	addPair(Tile::NineOfCharacters);
	addPair(Tile::OneOfCircles);
	addPair(Tile::NineOfCircles);
	addPair(Tile::NineOfBamboos);
	addPair(Tile::WhiteDragon);
	addPair(Tile::WestWind);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::AllTerminalsAndHornors));
	CHECK_EQUAL(1, r.patterns.count(Pattern::SevenPairs));
	CHECK_EQUAL(0, r.patterns.count(Pattern::TerminalOrHonorInEachSet));
}

TEST(DoublingFactorCounterTest, TerminalInEachSet)
{
	addPair(Tile::NineOfCharacters);
	addSequence(Tile::OneOfCharacters, false);
	addTriplet(Tile::NineOfCircles, false);
	addSequence(Tile::OneOfBamboos, false);
	addSequence(Tile::SevenOfBamboos, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::TerminalInEachSet));
	CHECK_EQUAL(0, r.patterns.count(Pattern::TerminalOrHonorInEachSet));
}

TEST(DoublingFactorCounterTest, Not_TerminalInEachSet_NotTerminalPair)
{
	addPair(Tile::WestWind);
	addSequence(Tile::OneOfCharacters, false);
	addTriplet(Tile::NineOfCircles, false);
	addSequence(Tile::OneOfBamboos, false);
	addSequence(Tile::SevenOfBamboos, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(0, r.patterns.count(Pattern::TerminalInEachSet));
}

TEST(DoublingFactorCounterTest, LittleThreeDragons)
{
	addPair(Tile::WhiteDragon);
	addTriplet(Tile::RedDragon, false);
	addTriplet(Tile::GreenDragon, false);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::SixOfBamboos, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::LittleThreeDragons));
	CHECK_EQUAL(1, r.patterns.count(Pattern::RedDragon));
	CHECK_EQUAL(1, r.patterns.count(Pattern::GreenDragon));
}

TEST(DoublingFactorCounterTest, HalfFlush)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::EastWind, false);
	addSequence(Tile::OneOfCharacters, false);
	addTriplet(Tile::FiveOfCharacters, false);
	addSequence(Tile::SixOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::HalfFlush));
}

TEST(DoublingFactorCounterTest, Flush)
{
	addPair(Tile::OneOfCharacters);
	addTriplet(Tile::TwoOfCharacters, false);
	addTriplet(Tile::FourOfCharacters, false);
	addSequence(Tile::SixOfCharacters, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::Flush));
}

TEST(DoublingFactorCounterTest, FourClosedTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addQuad(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::FourClosedTriplets));
}

TEST(DoublingFactorCounterTest, ThirteenOrphans)
{
	h.add(Tile::OneOfCharacters);
	h.add(Tile::NineOfCharacters);
	h.add(Tile::OneOfCircles);
	h.add(Tile::NineOfCircles);
	h.add(Tile::OneOfBamboos);
	h.add(Tile::NineOfBamboos);
	h.add(Tile::EastWind);
	h.add(Tile::SouthWind);
	h.add(Tile::WestWind);
	h.add(Tile::NorthWind);
	h.add(Tile::WhiteDragon);
	h.add(Tile::GreenDragon);
	addPair(Tile::RedDragon);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::ThirteenOrphans));
}

TEST(DoublingFactorCounterTest, NineGates)
{
	addTriplet(Tile::OneOfCharacters, false);
	h.add(Tile::TwoOfCharacters);
	h.add(Tile::ThreeOfCharacters);
	h.add(Tile::FourOfCharacters);
	h.add(Tile::FiveOfCharacters);
	h.add(Tile::SixOfCharacters);
	h.add(Tile::SevenOfCharacters);
	h.add(Tile::EightOfCharacters);
	addTriplet(Tile::NineOfCharacters, false);

	h.add(Tile::NineOfCharacters);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::NineGates));
}

TEST(DoublingFactorCounterTest, Not_NineGates_Open)
{
	addTriplet(Tile::OneOfCharacters, false);
	h.add(Tile::TwoOfCharacters);
	h.add(Tile::ThreeOfCharacters);
	h.add(Tile::FourOfCharacters);
	h.add(Tile::FiveOfCharacters);
	h.add(Tile::SixOfCharacters);
	h.add(Tile::SevenOfCharacters);
	h.add(Tile::EightOfCharacters);
	addTriplet(Tile::NineOfCharacters, true);

	h.add(Tile::NineOfCharacters);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(0, r.patterns.count(Pattern::NineGates));
}

TEST(DoublingFactorCounterTest, AllGreen)
{
	addPair(Tile::GreenDragon);
	addTriplet(Tile::TwoOfBamboos, false);
	addSequence(Tile::TwoOfBamboos, false);
	addTriplet(Tile::SixOfBamboos, false);
	addTriplet(Tile::EightOfBamboos, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::AllGreen));
}

TEST(DoublingFactorCounterTest, AllHonors)
{
	addPair(Tile::EastWind);
	addTriplet(Tile::SouthWind, false);
	addTriplet(Tile::WestWind, false);
	addTriplet(Tile::WhiteDragon, false);
	addTriplet(Tile::GreenDragon, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::AllHonors));
}

TEST(DoublingFactorCounterTest, AllHonors_SevenPairsForm)
{
	addPair(Tile::EastWind);
	addPair(Tile::SouthWind);
	addPair(Tile::WestWind);
	addPair(Tile::NorthWind);
	addPair(Tile::WhiteDragon);
	addPair(Tile::RedDragon);
	addPair(Tile::GreenDragon);	

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::AllHonors));
}

TEST(DoublingFactorCounterTest, AllTerminals)
{
	addPair(Tile::OneOfCharacters);
	addTriplet(Tile::NineOfCharacters, false);
	addTriplet(Tile::OneOfCircles, false);
	addTriplet(Tile::OneOfBamboos, false);
	addTriplet(Tile::NineOfBamboos, false);	

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::AllTerminals));
}

TEST(DoublingFactorCounterTest, BigThreeDragons)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::WhiteDragon, true);
	addTriplet(Tile::RedDragon, false);
	addTriplet(Tile::GreenDragon, false);
	addSequence(Tile::TwoOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::BigThreeDragons));
	CHECK_EQUAL(0, r.patterns.count(Pattern::WhiteDragon));
	CHECK_EQUAL(0, r.patterns.count(Pattern::RedDragon));
	CHECK_EQUAL(0, r.patterns.count(Pattern::GreenDragon));
}

TEST(DoublingFactorCounterTest, LittleFourWinds)
{
	addPair(Tile::EastWind);
	addTriplet(Tile::SouthWind, false);
	addTriplet(Tile::WestWind, false);
	addTriplet(Tile::NorthWind, false);
	addSequence(Tile::TwoOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::LittleFourWinds));
}

TEST(DoublingFactorCounterTest, BigFourWinds)
{
	addPair(Tile::OneOfBamboos);
	addTriplet(Tile::EastWind, false);
	addTriplet(Tile::SouthWind, false);
	addTriplet(Tile::WestWind, false);
	addTriplet(Tile::NorthWind, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::BigFourWinds));
}

TEST(DoublingFactorCounterTest, FourQuads)
{
	addPair(Tile::WestWind);
	addQuad(Tile::ThreeOfCharacters, false);
	addQuad(Tile::FourOfCircles, true);
	addQuad(Tile::FiveOfBamboos, true);
	addQuad(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::FourQuads));
}

TEST(DoublingFactorCounterTest, FourQuads_FourClosedTriplets)
{
	addPair(Tile::WestWind);
	addQuad(Tile::ThreeOfCharacters, false);
	addQuad(Tile::FourOfCircles, false);
	addQuad(Tile::FiveOfBamboos, false);
	addQuad(Tile::SevenOfCharacters, false);

	selfDrawn();
	auto r = c.report();

	CHECK_EQUAL(1, r.patterns.count(Pattern::FourQuads));
	CHECK_EQUAL(1, r.patterns.count(Pattern::FourClosedTriplets));
}

TEST(DoublingFactorCounterTest, MaxDoublingFactor)
{}
