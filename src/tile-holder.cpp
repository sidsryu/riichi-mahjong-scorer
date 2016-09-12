#include "tile-holder.h"
#include "type-define.h"
#include "tile-functor.h"
#include <algorithm>
#include <cassert>

using namespace std;

void TileHolder::add(Tile tile)
{
	tiles.push_back(tile);
	sort(tiles.begin(), tiles.end());	
}

void TileHolder::add(Meld meld)
{

}

bool TileHolder::empty() const
{
	return tiles.empty();
}

bool TileHolder::isNextTilePair()  const
{
	if (tiles.size() < 2) return false;
	return IsSame()(tiles.front(), tiles.at(1));	
}

bool TileHolder::isNextTilePon() const
{
	if (tiles.size() < 3) return false;
	return IsSame()(tiles.front(), tiles.at(1)) && IsSame()(tiles.front(), tiles.at(2));
}

bool TileHolder::isNextTileChii()  const
{
	auto tile = tiles.front();
	auto count = 1;

	for (auto it : tiles)
	{
		if (IsSame()(NextTile()(tile), it))
		{
			tile = it;
			count++;
		}

		if (count == 3)
		{
			return true;
		}
	}

	return false;
}

Pair TileHolder::popNextPair()
{
	assert(2 <= tiles.size());

	vector<Tile> pair;

	pair.push_back(tiles.front());
	tiles.erase(tiles.begin());

	pair.push_back(tiles.front());
	tiles.erase(tiles.begin());

	return pair;
}

Meld TileHolder::popNextPon()
{
	assert(3 <= tiles.size());

	vector<Tile> pon;

	pon.push_back(tiles.front());
	tiles.erase(tiles.begin());

	pon.push_back(tiles.front());
	tiles.erase(tiles.begin());

	pon.push_back(tiles.front());
	tiles.erase(tiles.begin());

	return { pon, false };
}

Meld TileHolder::popNextChii()
{
	vector<Tile> chii;

	auto tile = tiles.front();
	auto count = 0;

	for (auto it = tiles.begin(); it != tiles.end();)
	{
		if (count == 0 || IsSame()(NextTile()(tile), *it))
		{
			chii.push_back(*it);
			tile = *it;
			it = tiles.erase(it);
			count++;

			if (count == 3) break;
		}
		else
		{
			it++;
		}
	}

	assert(3 == chii.size());
	return { chii, false };
}
