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

TEST(PlayerHandTest, Pon)
{
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);

	h.bindPon({
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles
	});

	CHECK(h.isClaim());
}

TEST(PlayerHandTest, Kon)
{
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);

	h.bindKan({
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles
	});

	CHECK(h.isClaim());
}

TEST(PlayerHandTest, CloseKon)
{
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);
	h.add(Tile::OneOfCircles);

	h.bindCloseKan({
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles,
		Tile::OneOfCircles
	});

	CHECK(!h.isClaim());
}

TEST(PlayerHandTest, Chii)
{
	h.add(Tile::OneOfCircles);
	h.add(Tile::TwoOfCircles);
	h.add(Tile::ThreeOfCircles);

	h.bindChii({
		Tile::OneOfCircles,
		Tile::TwoOfCircles,
		Tile::ThreeOfCircles
	});

	CHECK(h.isClaim());
}
