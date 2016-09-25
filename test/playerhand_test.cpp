#include "CppUTest/TestHarness.h"
#include "player-hand.h"
#include "tile-define.h"
#include "meld.h"

TEST_GROUP(PlayerHandTest)
{
	PlayerHand h;
};

TEST(PlayerHandTest, LastDrawTile)
{
	h.add(Tile::OneOfCircles);
	CHECK(Tile::OneOfCircles == h.lastTile());

	h.add(Tile::TwoOfCircles);
	CHECK(Tile::TwoOfCircles == h.lastTile());
}

TEST(PlayerHandTest, Triplet)
{
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);

	h.bindTriplet({
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles
	});

	CHECK(!h.isClosedHand());
}

TEST(PlayerHandTest, Kon)
{
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);

	h.bindOpenQuad({
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles
	});

	CHECK(!h.isClosedHand());
}

TEST(PlayerHandTest, CloseKon)
{
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);

	h.bindClosedQuad({
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles
	});

	CHECK(h.isClosedHand());
}

TEST(PlayerHandTest, Sequence)
{
	h.add(Tile::OneOfCircles);
	h.add(Tile::TwoOfCircles);
	h.add(Tile::ThreeOfCircles);

	h.bindSequence({
		Tile::OneOfCircles,
		Tile::TwoOfCircles,
		Tile::ThreeOfCircles
	});

	CHECK(!h.isClosedHand());
}
