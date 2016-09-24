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
		auto next_tile = NextTile()(tile);
		auto last_tile = NextTile()(next_tile);

		vector<Tile> tiles {
			tile,
			next_tile,
			last_tile,
		};
		h.melds.push_back({ tiles, is_open });
		h.last_tile = last_tile;
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
	s.setRon();

	CHECK_EQUAL(30, m.total(false));
	CHECK_EQUAL(30, m.total());
}

TEST(MinipointCounterTest, ClosedRon)
{
	addNoPointHand();
	s.setRon();

	CHECK_EQUAL(30, m.total(false));
	CHECK_EQUAL(30, m.total());
}

TEST(MinipointCounterTest, SelfPick)
{
	addOpenNoPointHand();
	CHECK_EQUAL(22, m.total(false));
	CHECK_EQUAL(30, m.total());
}

TEST(MinipointCounterTest, NoPointsHandSelfPick)
{
	addNoPointHand();
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

	CHECK_EQUAL(25, m.total(false));
	CHECK_EQUAL(25, m.total());
}

TEST(MinipointCounterTest, EdgeWait)
{
	addOpenNoPointHand();
	s.setRon();

	h.last_tile = Tile::ThreeOfCharacters;
	CHECK_EQUAL(22, m.total(false));

	h.last_tile = Tile::SevenOfCharacters;
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, ClosedWait)
{
	addOpenNoPointHand();
	s.setRon();

	h.last_tile = Tile::EightOfCharacters;
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, PairWait)
{
	addOpenNoPointHand();
	s.setRon();

	h.last_tile = Tile::SouthWind;
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, ChooseHighestPointsWait)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::OneOfCircles, true);
	addSequence(Tile::OneOfBamboos, true);
	addSequence(Tile::ThreeOfCharacters, false);
	s.setRon();

	h.last_tile = Tile::ThreeOfCharacters;
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, ChooseHighestPointsWait_AnotherHandOrder)
{
	addPair(Tile::SouthWind);
	addSequence(Tile::ThreeOfCharacters, false);
	addSequence(Tile::OneOfCharacters, false);
	addSequence(Tile::OneOfCircles, true);
	addSequence(Tile::OneOfBamboos, true);	
	s.setRon();

	h.last_tile = Tile::ThreeOfCharacters;
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, DragonPair)
{
	addPair(Tile::WhiteDragon);
	addOpenNoPointsHandWithoutPair();
	s.setRon();
	
	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, OwnWindPair)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::SouthWind);

	addPair(Tile::SouthWind);
	addOpenNoPointsHandWithoutPair();
	s.setRon();

	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, RoundWindPair)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::SouthWind);
	
	addPair(Tile::EastWind);
	addOpenNoPointsHandWithoutPair();
	s.setRon();

	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, OwnAndRoundWindPair)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::EastWind);

	addPair(Tile::EastWind);
	addOpenNoPointsHandWithoutPair();
	s.setRon();

	CHECK_EQUAL(24, m.total(false));
}

TEST(MinipointCounterTest, SimpleOpenTriplet)
{
	addTriplet(Tile::EightOfCharacters, true);
	addOpenNoPointsHandWithoutOneMeld();
	s.setRon();

	CHECK_EQUAL(22, m.total(false));
}

TEST(MinipointCounterTest, SimpleClosedTriplet)
{
	addTriplet(Tile::EightOfCircles, false);
	addOpenNoPointsHandWithoutOneMeld();
	s.setRon();
	
	CHECK_EQUAL(24, m.total(false));
}

TEST(MinipointCounterTest, SimpleOpenQuad)
{
	addQuad(Tile::EightOfCircles, true);
	addOpenNoPointsHandWithoutOneMeld();
	s.setRon();
	
	CHECK_EQUAL(28, m.total(false));
}

TEST(MinipointCounterTest, SimpleClosedQuad)
{
	addQuad(Tile::EightOfCircles, false);
	addOpenNoPointsHandWithoutOneMeld();
	s.setRon();
	
	CHECK_EQUAL(36, m.total(false));
}

TEST(MinipointCounterTest, HornorOrTerminalOpenTriplet)
{
	addTriplet(Tile::WhiteDragon, true);
	addOpenNoPointsHandWithoutOneMeld();
	s.setRon();
	
	CHECK_EQUAL(24, m.total(false));
}

TEST(MinipointCounterTest, HornorOrTerminalClosedTriplet)
{
	addTriplet(Tile::WhiteDragon, false);
	addOpenNoPointsHandWithoutOneMeld();
	s.setRon();

	CHECK_EQUAL(28, m.total(false));
}

TEST(MinipointCounterTest, HornorOrTerminalOpenQuad)
{
	addQuad(Tile::WhiteDragon, true);
	addOpenNoPointsHandWithoutOneMeld();
	s.setRon();

	CHECK_EQUAL(36, m.total(false));
}

TEST(MinipointCounterTest, HornorOrTerminalClosedQuad)
{
	addQuad(Tile::WhiteDragon, false);
	addOpenNoPointsHandWithoutOneMeld();
	s.setRon();

	CHECK_EQUAL(52, m.total(false));
}

TEST(MinipointCounterTest, HighestPoints)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::EastWind);

	addQuad(Tile::OneOfCharacters, false);
	addQuad(Tile::RedDragon, false);
	addQuad(Tile::SouthWind, true);
	addSequence(Tile::SevenOfCircles, false);
	addPair(Tile::EastWind);

	CHECK_EQUAL(108, m.total(false));
	CHECK_EQUAL(110, m.total());
}
