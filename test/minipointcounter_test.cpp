#include "CppUTest/TestHarness.h"
#include "minipoint-counter.h"
#include "wining-state.h"
#include "type-define.h"
#include "tile-define.h"
#include "tile-functor.h"

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

	void addPon(Tile tile, bool is_open)
	{
		h.melds.push_back({ { tile, tile, tile }, is_open });
		h.last_tile = tile;
	}

	void addKan(Tile tile, bool is_open)
	{
		h.melds.push_back({ { tile, tile, tile, tile }, is_open });
		h.last_tile = tile;
	}

	void addChii(Tile tile, bool is_open)
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
		addPair(Tile::SevenOfCharacters);
		addChii(Tile::OneOfCircles, false);
		addChii(Tile::ThreeOfBamboos, false);
		addChii(Tile::FiveOfCharacters, false);
		addChii(Tile::SevenOfCharacters, false);
	}

	void addNoPointMeld()
	{
		addChii(Tile::OneOfCircles, false);
		addChii(Tile::ThreeOfBamboos, false);
		addChii(Tile::FiveOfCharacters, false);
		addChii(Tile::SevenOfCharacters, false);
	}

	void addMeldTestReady()
	{
		addPair(Tile::SevenOfCharacters);
		addChii(Tile::OneOfCircles, false);
		addChii(Tile::ThreeOfBamboos, false);
		addChii(Tile::FiveOfCharacters, false);
	}
};

TEST(MinipointCounterTest, SevenPairs)
{
	addPair(Tile::EastWind);
	addPair(Tile::NorthWind);
	addPair(Tile::ThreeOfCharacters);
	addPair(Tile::NineOfCircles);
	addPair(Tile::OneOfBamboos);
	addPair(Tile::GreenDragon);
	addPair(Tile::OneOfCharacters);

	CHECK_EQUAL(25, m.total());
}

TEST(MinipointCounterTest, BasicPoint)
{
	addNoPointHand();
	h.last_tile = Tile::SevenOfCharacters;

	CHECK_EQUAL(20, m.total());
}

TEST(MinipointCounterTest, ClosedRon)
{
	addNoPointHand();
	s.setRon();

	CHECK_EQUAL(30, m.total());
}

TEST(MinipointCounterTest, Tsumo)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCircles, false);
	addChii(Tile::ThreeOfBamboos, false);
	addChii(Tile::FiveOfCharacters, false);
	addChii(Tile::SevenOfCharacters, true);
	h.last_tile = Tile::SevenOfCharacters;

	CHECK_EQUAL(22, m.total());
}

TEST(MinipointCounterTest, EdgeWait)
{
	addPair(Tile::SevenOfCharacters);
	addChii(Tile::OneOfCircles, false);
	addChii(Tile::ThreeOfBamboos, false);
	addChii(Tile::FiveOfCharacters, true);
	addChii(Tile::SevenOfCharacters, false);
	h.last_tile = Tile::SevenOfCharacters;
	s.setRon();

	CHECK_EQUAL(22, m.total());
}

TEST(MinipointCounterTest, ClosedWait)
{
	addNoPointHand();
	h.last_tile = Tile::EightOfCharacters;
	s.setRon();

	CHECK_EQUAL(32, m.total());
}

TEST(MinipointCounterTest, PairWait)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCircles, false);
	addChii(Tile::ThreeOfBamboos, false);
	addChii(Tile::FiveOfCharacters, false);
	addChii(Tile::SevenOfCharacters, false);
	h.last_tile = Tile::SouthWind;
	s.setRon();

	CHECK_EQUAL(32, m.total());
}

TEST(MinipointCounterTest, ChooseWaitForHighestPoint)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCircles, false);
	addChii(Tile::ThreeOfBamboos, false);
	addChii(Tile::FiveOfCharacters, false);
	addPon(Tile::SevenOfCharacters, false);
	h.last_tile = Tile::SevenOfCharacters;

	CHECK_EQUAL(26, m.total());
}

TEST(MinipointCounterTest, DragonPair)
{
	addNoPointMeld();
	addPair(Tile::WhiteDragon);
	h.last_tile = Tile::WhiteDragon;

	CHECK_EQUAL(26, m.total());
}

TEST(MinipointCounterTest, OwnWindPair)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::SouthWind);

	addNoPointMeld();
	addPair(Tile::SouthWind);
	h.last_tile = Tile::SouthWind;
	

	CHECK_EQUAL(26, m.total());
}

TEST(MinipointCounterTest, RoundWindPair)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::SouthWind);

	addNoPointMeld();
	addPair(Tile::EastWind);
	h.last_tile = Tile::EastWind;

	CHECK_EQUAL(26, m.total());
}

TEST(MinipointCounterTest, OwnAndRoundWindPair)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::EastWind);

	addNoPointMeld();
	addPair(Tile::EastWind);
	h.last_tile = Tile::EastWind;

	CHECK_EQUAL(28, m.total());
}

TEST(MinipointCounterTest, SimpleOpenPon)
{	
	addMeldTestReady();
	addPon(Tile::EightOfCircles, true);
	h.last_tile = Tile::OneOfCircles;

	CHECK_EQUAL(24, m.total());
}

TEST(MinipointCounterTest, SimpleClosePon)
{
	addMeldTestReady();
	addPon(Tile::EightOfCircles, false);
	h.last_tile = Tile::OneOfCircles;

	CHECK_EQUAL(26, m.total());
}

TEST(MinipointCounterTest, SimpleOpenKan)
{
	addMeldTestReady();
	addKan(Tile::EightOfCircles, true);
	h.last_tile = Tile::OneOfCircles;

	CHECK_EQUAL(30, m.total());
}

TEST(MinipointCounterTest, SimpleCloseKan)
{
	addMeldTestReady();
	addKan(Tile::EightOfCircles, false);
	h.last_tile = Tile::OneOfCircles;

	CHECK_EQUAL(38, m.total());
}

TEST(MinipointCounterTest, HornorOrTerminalOpenPon)
{
	addMeldTestReady();
	addPon(Tile::SouthWind, true);
	h.last_tile = Tile::SouthWind;

	CHECK_EQUAL(26, m.total());
}

TEST(MinipointCounterTest, HornorOrTerminalClosePon)
{
	addMeldTestReady();
	addPon(Tile::SouthWind, false);
	h.last_tile = Tile::SouthWind;

	CHECK_EQUAL(30, m.total());
}

TEST(MinipointCounterTest, HornorOrTerminalOpenKan)
{
	addMeldTestReady();
	addKan(Tile::SouthWind, true);
	h.last_tile = Tile::SouthWind;

	CHECK_EQUAL(38, m.total());
}

TEST(MinipointCounterTest, HornorOrTerminalCloseKan)
{
	addMeldTestReady();
	addKan(Tile::SouthWind, false);
	h.last_tile = Tile::SouthWind;

	CHECK_EQUAL(54, m.total());
}

TEST(MinipointCounterTest, HighestPoints)
{
	s.setRountWind(Tile::EastWind);
	s.setOwnWind(Tile::EastWind);

	addKan(Tile::OneOfCharacters, false);
	addKan(Tile::RedDragon, false);
	addKan(Tile::SouthWind, true);
	addChii(Tile::SevenOfCircles, false);
	addPair(Tile::EastWind);

	CHECK_EQUAL(108, m.total());
}
