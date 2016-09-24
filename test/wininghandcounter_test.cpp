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

TEST_GROUP(WiningHandCounterTest)
{
	PlayerHand h;
	WiningState s;
	WiningHandCounter w { h, s };

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
			s.setClaim();
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
			s.setClaim();
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
			s.setClaim();
		}
		else
		{
			h.bindClosedQuad({ tile,tile,tile,tile });
		}
	}

	void selfDraw()
	{
		auto tile = h.lastTile();
		s.setTsumo(tile);
	}

	void winByDiscard()
	{
		auto tile = h.lastTile();
		s.setRon(tile);
	}
};

TEST(WiningHandCounterTest, SevenPairs)
{
	addPair(Tile::EastWind);
	addPair(Tile::NorthWind);
	addPair(Tile::ThreeOfCharacters);
	addPair(Tile::NineOfCircles);
	addPair(Tile::OneOfBamboos);
	addPair(Tile::GreenDragon);
	addPair(Tile::OneOfCharacters);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::SevenPairs));
}

TEST(WiningHandCounterTest, Not_SevenPairs_FourSuit)
{
	addPair(Tile::EastWind);
	addPair(Tile::NorthWind);
	addPair(Tile::ThreeOfCharacters);
	addPair(Tile::NineOfCircles);
	addPair(Tile::OneOfBamboos);
	addPair(Tile::GreenDragon);
	addPair(Tile::GreenDragon);

	selfDraw();
	w.compute();

	CHECK(!w.hasPattern(Pattern::SevenPairs));
}

TEST(WiningHandCounterTest, NoPointsHand)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::NoPointsHand));
}

TEST(WiningHandCounterTest, Not_NoPointsHand_Open)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, true);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(w.isPattenEmpty());
}

TEST(WiningHandCounterTest, Not_NoPointsHand_NotMultiWait)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);

	h.add(Tile::NineOfCircles);
	h.add(Tile::EightOfCircles);
	h.add(Tile::SevenOfCircles);

	selfDraw();
	w.compute();

	CHECK(!w.hasPattern(Pattern::NoPointsHand));
}

TEST(WiningHandCounterTest, Not_NoPointsHand_DragonPair)
{
	addPair(Tile::WhiteDragon);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(!w.hasPattern(Pattern::NoPointsHand));
}

TEST(WiningHandCounterTest, NoPointsHand_ScoringWindPair)
{
	s.setRountWind(Tile::EastWind);

	addPair(Tile::EastWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(!w.hasPattern(Pattern::NoPointsHand));
}

TEST(WiningHandCounterTest, OneSetOfIdenticalSequences)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);
	addTriplet(Tile::NineOfBamboos, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::OneSetOfIdenticalSequences));
}

TEST(WiningHandCounterTest, Not_OneSetOfIdenticalSequences_Open)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfCircles, false);
	addTriplet(Tile::NineOfBamboos, true);

	selfDraw();
	w.compute();

	CHECK(w.isPattenEmpty());
}

TEST(WiningHandCounterTest, ThreeColourStraights)
{
	addPair(Tile::WestWind);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, true);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::ThreeColourStraights));
}

TEST(WiningHandCounterTest, Straight)
{
	addPair(Tile::WestWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::FourOfCharacters, false);
	addSequence(Tile::SevenOfCharacters, false);
	addTriplet(Tile::OneOfBamboos, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::Straight));
}

TEST(WiningHandCounterTest, TwoSetsOfIdenticalSequences)
{
	addPair(Tile::WestWind);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::ThreeOfCircles, false);
	addSequence(Tile::ThreeOfCircles, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::TwoSetsOfIdenticalSequences));
	CHECK(!w.hasPattern(Pattern::SevenPairs));
}

TEST(WiningHandCounterTest, Not_TwoSetsOfIdenticalSequences_Open)
{
	addPair(Tile::WestWind);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::ThreeOfCircles, false);
	addSequence(Tile::ThreeOfCircles, false);

	h.bindSequence({
		Tile::ThreeOfCircles,
		Tile::FourOfCircles,
		Tile::FiveOfCircles
	});
	s.setClaim();

	selfDraw();
	w.compute();

	CHECK(!w.hasPattern(Pattern::TwoSetsOfIdenticalSequences));
}

TEST(WiningHandCounterTest, AllTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, true);
	addTriplet(Tile::TwoOfCircles, true);
	addTriplet(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::SevenOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::AllTriplets));
}

TEST(WiningHandCounterTest, ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addQuad(Tile::ThreeOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, Not_ThreeClosedTriplets_Ron)
{
	addPair(Tile::WestWind);
	addSequence(Tile::SevenOfCharacters, false);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addTriplet(Tile::ThreeOfBamboos, false);
		
	winByDiscard();
	w.compute();

	CHECK(!w.hasPattern(Pattern::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, ThreeClosedTriplets_Ron)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addSequence(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::ThreeOfBamboos, false);

	winByDiscard();
	w.compute();

	CHECK(w.hasPattern(Pattern::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, AllTriplets_ThreeClosedTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::OneOfCharacters, false);
	addTriplet(Tile::TwoOfCircles, false);
	addTriplet(Tile::ThreeOfBamboos, false);
	addTriplet(Tile::SevenOfCharacters, false);

	winByDiscard();
	w.compute();

	CHECK(w.hasPattern(Pattern::AllTriplets));
	CHECK(w.hasPattern(Pattern::ThreeClosedTriplets));
}

TEST(WiningHandCounterTest, ThreeColourTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::ThreeOfCharacters, false);
	addTriplet(Tile::ThreeOfCircles, false);
	addQuad(Tile::ThreeOfBamboos, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::ThreeColourTriplets));
}

TEST(WiningHandCounterTest, ThreeQuads)
{
	addPair(Tile::WestWind);
	addQuad(Tile::ThreeOfCharacters, false);
	addQuad(Tile::FourOfCircles, true);
	addQuad(Tile::FiveOfBamboos, true);
	addSequence(Tile::SevenOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::ThreeQuads));
}

TEST(WiningHandCounterTest, ThreeQuads_ThreeClosedTriplets_AllTriplets)
{
	addPair(Tile::WestWind);
	addQuad(Tile::ThreeOfCharacters, false);
	addQuad(Tile::FourOfCircles, false);
	addQuad(Tile::FiveOfBamboos, false);
	addTriplet(Tile::SevenOfCharacters, true);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::ThreeQuads));
	CHECK(w.hasPattern(Pattern::ThreeClosedTriplets));
	CHECK(w.hasPattern(Pattern::AllTriplets));
}

TEST(WiningHandCounterTest, AllSimples)
{
	addPair(Tile::ThreeOfCharacters);
	addSequence(Tile::FiveOfCharacters, false);
	addTriplet(Tile::ThreeOfCircles, false);
	addSequence(Tile::ThreeOfBamboos, false);
	addSequence(Tile::SixOfBamboos, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::AllSimples));
}

TEST(WiningHandCounterTest, HonorTiles_Dragon)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addTriplet(Tile::WhiteDragon, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::WhiteDragon));
}

TEST(WiningHandCounterTest, HonorTiles_Wind)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::SouthWind);

	addPair(Tile::WhiteDragon);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::TwoOfCircles, false);
	addSequence(Tile::TwoOfBamboos, false);
	addTriplet(Tile::EastWind, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::EastWind));

	s.setOwnWind(Tile::EastWind);	
	w.compute();

	CHECK(w.hasPattern(Pattern::DoubleEastWind));

	s.setRountWind(Tile::SouthWind);
	w.compute();

	CHECK(w.hasPattern(Pattern::EastWind));
}

TEST(WiningHandCounterTest, TerminalOrHonorInEachSet)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::WhiteDragon, false);
	addTriplet(Tile::OneOfCharacters, false);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::SevenOfBamboos, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::TerminalOrHonorInEachSet));
}

TEST(WiningHandCounterTest, AllTerminalsAndHornors_AllTriplets)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::NorthWind, true);
	addTriplet(Tile::OneOfCharacters, true);
	addTriplet(Tile::NineOfCircles, false);
	addTriplet(Tile::NineOfBamboos, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::AllTerminalsAndHornors));
	CHECK(w.hasPattern(Pattern::AllTriplets));
}

TEST(WiningHandCounterTest, AllTerminalsAndHornors_SevenPairs)
{
	addPair(Tile::OneOfCharacters);
	addPair(Tile::NineOfCharacters);
	addPair(Tile::OneOfCircles);
	addPair(Tile::NineOfCircles);
	addPair(Tile::NineOfBamboos);
	addPair(Tile::WhiteDragon);
	addPair(Tile::WestWind);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::AllTerminalsAndHornors));
	CHECK(w.hasPattern(Pattern::SevenPairs));
}

TEST(WiningHandCounterTest, TerminalInEachSet)
{
	addPair(Tile::NineOfCharacters);
	addSequence(Tile::OneOfCharacters, false);
	addTriplet(Tile::NineOfCircles, false);
	addSequence(Tile::OneOfBamboos, false);
	addSequence(Tile::SevenOfBamboos, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::TerminalInEachSet));
}

TEST(WiningHandCounterTest, LittleThreeDragons)
{
	addPair(Tile::WhiteDragon);
	addTriplet(Tile::RedDragon, false);
	addTriplet(Tile::GreenDragon, false);
	addSequence(Tile::TwoOfCharacters, false);
	addSequence(Tile::SixOfBamboos, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::LittleThreeDragons));
}

TEST(WiningHandCounterTest, HalfFlush)
{
	addPair(Tile::WestWind);
	addTriplet(Tile::EastWind, false);
	addSequence(Tile::OneOfCharacters, false);
	addTriplet(Tile::FiveOfCharacters, false);
	addSequence(Tile::SixOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::HalfFlush));
}

TEST(WiningHandCounterTest, Flush)
{
	addPair(Tile::OneOfCharacters);
	addTriplet(Tile::TwoOfCharacters, false);
	addTriplet(Tile::FourOfCharacters, false);
	addSequence(Tile::SixOfCharacters, false);
	addSequence(Tile::SevenOfCharacters, false);

	selfDraw();
	w.compute();

	CHECK(w.hasPattern(Pattern::Flush));
}
