#include "tile-holder.h"
#include "tile-functor.h"
#include "pair.h"
#include "meld.h"
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
	melds.push_back(meld);
	sort(melds.begin(), melds.end(), [](const auto& lhs, const auto& rhs) {
		return lhs.frontTile() < rhs.frontTile();
	});
}

bool TileHolder::empty() const
{
	return tiles.empty() && melds.empty();
}

bool TileHolder::isNextTilePair()  const
{
	if (tiles.size() < 2) return false;
	return IsSame()(tiles.front(), tiles.at(1));
}

bool TileHolder::isNextTileTripletOrQuad() const
{
	if (tiles.empty())
	{
		const auto& meld = melds.front();
		return meld.isTripletOrQuad();
	}

	if (tiles.size() < 3) return false;
	return IsSame()(tiles.front(), tiles.at(1)) && IsSame()(tiles.front(), tiles.at(2));
}

bool TileHolder::isNextTileSequence()  const
{
	if (tiles.empty())
	{
		const auto& meld = melds.front();
		return meld.isSequence();
	}

	if (tiles.size() < 3) return false;

	auto tile = tiles.front();
	auto count = 1;

	for (auto it : tiles)
	{
		if (!IsHonor()(it) && IsSame()(NextTile()(tile), it))
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

Meld TileHolder::popNextTripletOrQuad()
{
	if (tiles.empty())
	{
		for (auto it = melds.begin(); it != melds.end(); it++)
		{
			if (it->isTripletOrQuad())
			{
				auto meld = *it;
				melds.erase(it);

				return meld;
			}
		}
	}

	if (3 <= tiles.size())
	{
		if (IsSame()(tiles.front(), tiles.at(1)) && IsSame()(tiles.front(), tiles.at(2)))
		{
			vector<Tile> triplet;

			triplet.push_back(tiles.front());
			tiles.erase(tiles.begin());

			triplet.push_back(tiles.front());
			tiles.erase(tiles.begin());

			triplet.push_back(tiles.front());
			tiles.erase(tiles.begin());

			return { triplet, false };
		}
	}

	assert(false);
	return { {}, false };
}

Meld TileHolder::popNextSequence()
{
	if (tiles.empty())
	{
		for (auto it = melds.begin(); it != melds.end(); it++)
		{
			if (it->isSequence())
			{
				auto meld = *it;
				melds.erase(it);

				return meld;
			}
		}
	}

	if (3 <= tiles.size())
	{
		vector<Tile> sequence;

		auto tile = tiles.front();
		auto count = 0;

		for (auto it = tiles.begin(); it != tiles.end();)
		{
			if (count == 0 || (!IsHonor()(*it) && IsSame()(NextTile()(tile), *it)))
			{
				sequence.push_back(*it);
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

		if (3 == sequence.size())
		{
			return { sequence, false };
		}
	}

	assert(false);
	return { {}, false };
}
