#include "tile-functor.h"
#include "tile-define.h"
#include <cassert>

bool IsSame::operator()(const Tile& lhv, const Tile& rhv) const
{
	// red fives' units is 1
	return static_cast<int>(lhv) / 10 == static_cast<int>(rhv) / 10;
}

bool IsSimple::operator()(const Tile& tile) const
{
	auto code = static_cast<int>(tile);
	auto suit = code / 100;
	auto number = code / 10 % 10;

	return (1 <= suit && suit <= 3) && (2 <= number && number <= 8);
}

bool IsTerminal::operator()(const Tile& tile) const
{
	auto code = static_cast<int>(tile);
	auto suit = code / 100;
	auto number = code / 10 % 10;

	return (1 <= suit && suit <= 3) && (1 == number || number == 9);
}

bool IsDragon::operator()(const Tile& tile) const
{
	auto suit = static_cast<int>(tile) / 100;
	return suit == 5;
}

bool IsHonor::operator()(const Tile& tile) const
{
	auto suit = static_cast<int>(tile) / 100;
	return suit == 4 || suit == 5;
}

bool IsRedFive::operator()(const Tile& tile) const
{
	auto red = static_cast<int>(tile) % 10;	
	return red == 1;
}

Tile NextTile::operator()(const Tile& tile) const
{
	auto code = static_cast<int>(tile);
	auto suit = code / 100;
	auto number = code / 10 % 10;
	
	number++;

	if (1 <= suit && suit <= 3 && 9 < number) number = 1;
	if (4 == suit && 4 < number) number = 1;
	if (5 == suit && 3 < number) number = 1;

	auto next = suit * 100 + number * 10;
	return static_cast<Tile>(next);
}
