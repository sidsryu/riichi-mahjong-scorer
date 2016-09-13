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
};

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

TEST(MinipointCounterTest, SingleWait)
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

TEST(MinipointCounterTest, MeldSingleWait)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCircles, false);
	addChii(Tile::ThreeOfBamboos, false);
	addChii(Tile::FiveOfCharacters, true);
	addPon(Tile::SevenOfCharacters, false);
	h.last_tile = Tile::SevenOfCharacters;
	s.setRon();

	CHECK_EQUAL(22, m.total());
}

TEST(MinipointCounterTest, ChooseWaitForHighestPoint)
{
	addPair(Tile::SouthWind);
	addChii(Tile::OneOfCircles, false);
	addChii(Tile::ThreeOfBamboos, false);
	addChii(Tile::FiveOfCharacters, false);
	addPon(Tile::SevenOfCharacters, false);
	h.last_tile = Tile::SevenOfCharacters;

	CHECK_EQUAL(24, m.total());
}

