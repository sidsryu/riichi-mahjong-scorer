#include "CppUTest/TestHarness.h"
#include "player-hand.h"
#include "tile-define.h"

TEST_GROUP(PlayerHandTest)
{
	PlayerHand h;
};

TEST(PlayerHandTest, LastDrawTile)
{
	h.tsumo(Tile::OneOfCircles);
	CHECK(Tile::OneOfCircles == h.lastTile());

	h.ron(Tile::TwoOfCircles);
	CHECK(Tile::TwoOfCircles == h.lastTile());
}

TEST(PlayerHandTest, Ron)
{
	h.tsumo(Tile::OneOfCircles);
	CHECK(!h.isRon());

	h.ron(Tile::TwoOfCircles);
	CHECK(h.isRon());
}

TEST(PlayerHandTest, Draw)
{
	h.tsumo(Tile::OneOfCircles);
	CHECK_EQUAL(1, h.countTile(Tile::OneOfCircles));

	h.ron(Tile::TwoOfCircles);
	CHECK_EQUAL(1, h.countTile(Tile::TwoOfCircles));
}

TEST(PlayerHandTest, Discard)
{
	h.tsumo(Tile::OneOfCircles);
	h.discard(Tile::OneOfCircles);

	CHECK_EQUAL(0, h.countTile(Tile::OneOfCircles));
}

TEST(PlayerHandTest, Pon)
{
	h.tsumo(Tile::OneOfCircles);
	h.tsumo(Tile::OneOfCircles);	
	h.pon(Tile::OneOfCircles);

	CHECK(h.isClaim());
	CHECK_EQUAL(3, h.countTile(Tile::OneOfCircles));
}

TEST(PlayerHandTest, Kon)
{
	h.tsumo(Tile::OneOfCircles);
	h.tsumo(Tile::OneOfCircles);
	h.tsumo(Tile::OneOfCircles);
	h.kon(Tile::OneOfCircles);

	CHECK(h.isClaim());
	CHECK_EQUAL(4, h.countTile(Tile::OneOfCircles));
}

TEST(PlayerHandTest, Chii)
{
	h.tsumo(Tile::OneOfCircles);
	h.tsumo(Tile::TwoOfCircles);
	h.chii(Tile::ThreeOfCircles);

	CHECK(h.isClaim());
	CHECK_EQUAL(1, h.countTile(Tile::ThreeOfCircles));
}
