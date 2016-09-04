#include "tile-holder.h"
#include <algorithm>

using namespace std;

void TileHolder::add(Tile tile)
{
	tiles.push_back(tile);
	sort(tiles.begin(), tiles.end());	
}

bool TileHolder::empty() const
{
	return tiles.empty();
}

bool TileHolder::isNextTilePair()  const
{
	if (tiles.size() < 2) return false;
	return tiles.front() == tiles.at(1);	
}

bool TileHolder::isNextTilePon() const
{
	if (tiles.size() < 3) return false;
	return tiles.front() == tiles.at(1) && tiles.front() == tiles.at(2);
}

bool TileHolder::isNextTileChii()  const
{
	auto tile = tiles.front();
	auto count = 1;

	for (auto it : tiles)
	{
		if (tile != it)
		{
			tile = it;
			count++;
		}

		if (count == 3)
		{
			return 2 == static_cast<int>(tile) - static_cast<int>(tiles.front());
		}
	}

	return false;
}

Tile TileHolder::popFront()
{
	auto tile = tiles.front();
	tiles.erase(tiles.begin());
	return tile;
}

void TileHolder::popFrontChii(std::function<void(Tile)> fn)
{
	auto tile = tiles.front();
	auto count = 0;

	for (auto it = tiles.begin(); it != tiles.end();)
	{
		if (count == 0 || tile != *it)
		{
			fn(*it);
			it = tiles.erase(it);
			count++;

			if (count == 3) return;
		}
		else
		{
			it++;
		}
	}
}
