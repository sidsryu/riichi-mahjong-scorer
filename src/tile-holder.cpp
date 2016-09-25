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

Pair TileHolder::popPairWithFrontTile()
{
	if (2 <= tiles.size())
	{
		if (IsSame()(tiles[0], tiles[1]))
		{
			return popTiles({ 0, 1 });
		}
	}

	return {};
}

Meld TileHolder::popTripletOrQuadWithFrontTile()
{
	if (3 <= tiles.size())
	{
		if (IsSame()(tiles[0], tiles[1]) && IsSame()(tiles[0], tiles[2]))
		{
			return { popTiles({ 0, 1, 2 }), false };
		}
	}

	if (tiles.empty())
	{
		return popTripletOrQuadMeld();
	}

	return {};
}

Meld TileHolder::popSequenceWithFrontTile()
{
	if (3 <= tiles.size())
	{
		if (!IsHonor()(tiles[0]))
		{
			set<int> pop_indices { 0 };
			Tile next_tile = NextTile()(tiles[0]);

			for (size_t i = 0; i < tiles.size(); i++)
			{
				if (IsSame()(next_tile, tiles[i]))
				{
					next_tile = NextTile()(next_tile);
					pop_indices.insert(i);
				}

				if (3 == pop_indices.size())
				{
					return { popTiles(pop_indices), false };
				}
			}
		}
	}

	if (tiles.empty())
	{
		return popSequenceMeld();
	}

	return {};
}

vector<Tile> TileHolder::popTiles(set<int> indices)
{
	vector<Tile> poped_tiles;

	auto index = 0;
	auto it = tiles.begin();
	while (it != tiles.end())
	{
		auto will_pop = indices.find(index);
		if (will_pop != indices.end())
		{
			poped_tiles.push_back(*it);
			it = tiles.erase(it);
		}
		else
		{
			it++;
		}

		index++;
	}

	return poped_tiles;
}

Meld TileHolder::popTripletOrQuadMeld()
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

	return {};
}

Meld TileHolder::popSequenceMeld()
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

	return {};
}
