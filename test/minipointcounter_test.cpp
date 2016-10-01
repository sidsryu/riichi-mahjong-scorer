#include "CppUTest/TestHarness.h"
#include "minipoint-counter.h"
#include "wining-state.h"
#include "tile-define.h"
#include "tile-functor.h"
#include "wining-hand.h"
#include "pair.h"
#include "meld.h"

using namespace std;

TEST_GROUP(MinipointCounterTest)
{
	WiningState s;
	WiningHand h;
	MinipointCounter m { h, s };

	void addPair(Tile tile)
	{
		h.pairs.push_back(vector<Tile>{ tile, tile });
		h.last_tile = tile;
	}

	void addTriplet(Tile tile, bool is_open)
	{
		h.melds.push_back({ { tile, tile, tile }, is_open });
		h.last_tile = tile;
	}

	void addQuad(Tile tile, bool is_open)
	{
		h.melds.push_back({ { tile, tile, tile, tile }, is_open });
		h.last_tile = tile;
	}

	void addSequence(Tile tile, bool is_open)
	{
		auto next = NextTile()(tile);
		auto last = NextTile()(next);

		vector<Tile> tiles {
			tile,
			next,
			last,
		};
		h.melds.push_back({ tiles, is_open });
		h.last_tile = last;
	}

	void addNoPointHand()
	{
		addPair(Tile::SouthWind);
		addSequence(Tile::OneOfCharacters, false);
		addSequence(Tile::TwoOfCircles, false);
		addSequence(Tile::TwoOfBamboos, false);
		addSequence(Tile::SevenOfCharacters, false);
	}

	void addOpenNoPointHand()
	{
		// Terminal or honor in each set
		addPair(Tile::SouthWind);
		addSequence(Tile::OneOfCharacters, false);
		addSequence(Tile::OneOfCircles, true);
		addSequence(Tile::OneOfBamboos, true);
		addSequence(Tile::SevenOfCharacters, false);
	}

	void addOpenNoPointsHandWithoutPair()
	{
		addSequence(Tile::TwoOfCharacters, false);
		addSequence(Tile::TwoOfCircles, true);
		addSequence(Tile::TwoOfBamboos, true);
		addSequence(Tile::SevenOfCharacters, false);
	}

	void addOpenNoPointsHandWithoutOneMeld()
	{
		addPair(Tile::SouthWind);
		addSequence(Tile::TwoOfCircles, true);
		addSequence(Tile::TwoOfBamboos, true);
		addSequence(Tile::TwoOfCharacters, false);
	}
};

TEST(MinipointCounterTest, BasicPoints_OpenNoPointsHand)
{
	addOpenNoPointHand();
	s.winByDiscard();

	CHECK_EQUAL(30, m.total(false));
	CHECK_EQUAL(30, m.total());
}

TEST(MinipointCounterTest, ClosedWinByDiscard)
{
	addNoPointHand();
	s.winByDiscard();

	CHECK_EQUAL(30, m.total(false));
	CHECK_EQUAL(30, m.total());
}

TEST(MinipointCounterTest, SelfDrawn)
{
	addOpenNoPointHand();
	s.selfDrawn();

	CHECK_EQUAL(22, m.total(false));
	CHECK_EQUAL(30, m.total());
}

TEST(MinipointCounterTest, NoPointsHandSelfDrawn)
{
	addNoPointHand();
	s.selfDrawn();

	CHECK_EQUAL(20, m.total(false));
	CHECK_EQUAL(20, m.total());
}

TEST(MinipointCounterTest, SevenPairs)
{
	addPair(Tile::EastWind);
	addPair(Tile::NorthWind);
	addPair(Tile::ThreeOfCharacters);
	addPair(Tile::NineOfCircles);
	addPair(Tile::OneOfBamboos);
	addPair(Tile::GreenDragon);
	addPair(Tile::OneOfCharacters);
	s.selfDrawn();

	CHECK_EQUAL(25, m.total(false));
	CHECK_EQUAL(25, m.total());
}

TEST(MinipointCounterTest, EdgeWait)
{
	addOpenNoPointHand();

	h.last_tile = Tile::ThreeOfCharacters;
	s.winByDiscard();
	CHECK_EQUAL(22, m.total(false));

	h.last_tile = Tile::SevenOfCharacters;
	s.winByDiscard();
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, ClosedWait)
{
	addOpenNoPointHand();

	h.last_tile = Tile::EightOfCharacters;
	s.winByDiscard();
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, PairWait)
{
	addOpenNoPointHand();

	h.last_tile = Tile::SouthWind;
	s.winByDiscard();
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, ChooseHighestPointsWait)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::OneOfCircles, true);
	addSequence(Tile::OneOfBamboos, true);
	addSequence(Tile::ThreeOfCharacters, false);

	h.last_tile = Tile::ThreeOfCharacters;
	s.winByDiscard();
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, ChooseHighestPointsWait_AnotherHandOrder)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::ThreeOfCharacters, false);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::OneOfCircles, true);
	addSequence(Tile::OneOfBamboos, true);

	h.last_tile = Tile::ThreeOfCharacters;
	s.winByDiscard();
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, DragonPair)
{
	addPair(Tile::WhiteDragon);
	addOpenNoPointsHandWithoutPair();
	s.winByDiscard();

	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, OwnWindPair)
{
	s.setRoundWind(Tile::EastWind);
	s.setSeatWind(Tile::SouthWind);

	addPair(Tile::SouthWind);
	addOpenNoPointsHandWithoutPair();
	s.winByDiscard();

	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, RoundWindPair)
{
	s.setRoundWind(Tile::EastWind);
	s.setSeatWind(Tile::SouthWind);

	addPair(Tile::EastWind);
	addOpenNoPointsHandWithoutPair();
	s.winByDiscard();

	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, OwnAndRoundWindPair)
{
	s.setRoundWind(Tile::EastWind);
	s.setSeatWind(Tile::EastWind);

	addPair(Tile::EastWind);
	addOpenNoPointsHandWithoutPair();
	s.winByDiscard();

	CHECK_EQUAL(24, m.total(false));
}

TEST(MinipointCounterTest, SimpleOpenTriplet)
{
	addTriplet(Tile::EightOfCharacters, true);
	addOpenNoPointsHandWithoutOneMeld();
	s.winByDiscard();

	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, SimpleClosedTriplet)
{
	addTriplet(Tile::EightOfCircles, false);
	addOpenNoPointsHandWithoutOneMeld();
	s.winByDiscard();

	CHECK_EQUAL(24, m.total(false));
}

TEST(MinipointCounterTest, SimpleOpenQuad)
{
	addQuad(Tile::EightOfCircles, true);
	addOpenNoPointsHandWithoutOneMeld();
	s.winByDiscard();

	CHECK_EQUAL(28, m.total(false));
}

TEST(MinipointCounterTest, SimpleClosedQuad)
{
	addQuad(Tile::EightOfCircles, false);
	addOpenNoPointsHandWithoutOneMeld();
	s.winByDiscard();

	CHECK_EQUAL(36, m.total(false));
}

TEST(MinipointCounterTest, HornorOrTerminalOpenTriplet)
{
	addTriplet(Tile::WhiteDragon, true);
	addOpenNoPointsHandWithoutOneMeld();
	s.winByDiscard();

	CHECK_EQUAL(24, m.total(false));
}

TEST(MinipointCounterTest, HornorOrTerminalClosedTriplet)
{
	addTriplet(Tile::WhiteDragon, false);
	addOpenNoPointsHandWithoutOneMeld();
	s.winByDiscard();

	CHECK_EQUAL(28, m.total(false));
}

TEST(MinipointCounterTest, HornorOrTerminalOpenQuad)
{
	addQuad(Tile::WhiteDragon, true);
	addOpenNoPointsHandWithoutOneMeld();
	s.winByDiscard();

	CHECK_EQUAL(36, m.total(false));
}

TEST(MinipointCounterTest, HornorOrTerminalClosedQuad)
{
	addQuad(Tile::WhiteDragon, false);
	addOpenNoPointsHandWithoutOneMeld();
	s.winByDiscard();

	CHECK_EQUAL(52, m.total(false));
}

TEST(MinipointCounterTest, HighestPoints)
{
	s.setRoundWind(Tile::EastWind);
	s.setSeatWind(Tile::EastWind);

	addQuad(Tile::OneOfCharacters, false);
	addQuad(Tile::RedDragon, false);
	addQuad(Tile::SouthWind, true);
	addSequence(Tile::SevenOfCircles, false);
	addPair(Tile::EastWind);

	s.selfDrawn();

	CHECK_EQUAL(108, m.total(false));
	CHECK_EQUAL(110, m.total());
}
