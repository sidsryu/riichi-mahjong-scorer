#include "value-tiles-recognizer.h"
#include "wining-state.h"
#include "pattern-define.h"
#include "tile-functor.h"
#include "tile-define.h"
#include "meld.h"

using namespace std;

void ValueTilesRecognizer::reset()
{
	value_tiles.clear();
}

void ValueTilesRecognizer::check(const Pair& pair)
{}

void ValueTilesRecognizer::check(const Meld& meld)
{
	if (meld.isValueTiles(state))
	{
		auto tile = meld.frontTile();
		value_tiles.insert(tile);
	}
}

std::set<Pattern> ValueTilesRecognizer::recognize()
{
	set<Pattern> patterns;

	for (auto it : value_tiles)
	{
		if (IsSame()(it, Tile::WhiteDragon)) patterns.insert(Pattern::WhiteDragon);
		if (IsSame()(it, Tile::GreenDragon)) patterns.insert(Pattern::GreenDragon);
		if (IsSame()(it, Tile::RedDragon)) patterns.insert(Pattern::RedDragon);

		if (IsSame()(state.roundWind(), state.seatWind()))
		{
			if (IsSame()(it, Tile::EastWind)) patterns.insert(Pattern::DoubleEastWind);
			if (IsSame()(it, Tile::SouthWind)) patterns.insert(Pattern::DoubleSouthWind);
			if (IsSame()(it, Tile::WestWind)) patterns.insert(Pattern::DoubleWestWind);
			if (IsSame()(it, Tile::NorthWind)) patterns.insert(Pattern::DoubleNorthWind);
		}
		else
		{
			if (IsSame()(it, Tile::EastWind)) patterns.insert(Pattern::EastWind);
			if (IsSame()(it, Tile::SouthWind)) patterns.insert(Pattern::SouthWind);
			if (IsSame()(it, Tile::WestWind)) patterns.insert(Pattern::WestWind);
			if (IsSame()(it, Tile::NorthWind)) patterns.insert(Pattern::NorthWind);
		}
	}
	
	return patterns;
}
