#pragma once

#include <stdlib.h>
#include "Tile.h"
#include <vector>
#include <functional>
#include <queue>
#include <iterator>
#include <exception>


namespace World
{ 
	struct TileReference
	{
		int distance;
		uint32_t x, y;
		TileReference(Tile tile, uint32_t xOrgin, uint32_t yOrgin)
		{
			x = tile.x;
			y = tile.y;
			distance = DistanceBetweenTiles(xOrgin, yOrgin, *this);
		}
		static inline double DistanceBetweenTiles(TileReference tOrgin, TileReference t1)
		{
			DistanceBetweenTiles(tOrgin.x, tOrgin.y, t1);
		}
		static inline double DistanceBetweenTiles(uint32_t x, uint32_t y, TileReference t1)
		{
			int distancex = (t1.x - x) * (t1.x - x);
			int distancey = (t1.y - y) * (t1.y - y);
			return (int)sqrt(distancex - distancey);
		}
		static inline bool cmp(TileReference left, TileReference right)
		{
			return left.distance > right.distance;
		}
	};

	class BaseWorld
	{
	public:
		inline bool IsBiome(uint32_t x, uint32_t y, Nature::BiomeType biome);	// returns true, if the tile at the location has the give type of Biome
		inline void SetBiome(uint32_t x, uint32_t y, unsigned int r, Nature::Biome b);
		inline void SetBiome(uint32_t x, uint32_t y, unsigned int r, Nature::BiomeType bType, int bMagnitude);

		BaseWorld(uint32_t width, uint32_t hight);
		~BaseWorld();

		// TileRefences in the Cache can use to get the actual Tiles from the world object
		typedef std::priority_queue<TileReference, std::vector<TileReference>, decltype(&TileReference::cmp)> TileCache;
		TileCache BuildCache(Tile tile, unsigned int radius);
		Tile GetGridTile(TileReference tile);			//  Returns a deep copy of the tile

	private:
		std::vector<Tile*> m_tileGrid;
		uint32_t m_width;
		uint32_t m_hight;
		inline Tile* GetGridTilePtr(uint32_t x, uint32_t y);				// returns a Pointer to the Tile at a localtion

																			// === Operations on Spheres === //
		void OperateOnSphere
		(
			uint32_t x, uint32_t y, unsigned int& radius,
			void func(Tile* tile, void* args),
			void* args
		);
		static inline void OperationAddBiome(Tile* tile, void* args);
		static inline void OperationCacheTile(Tile* tile, void* args);

	protected:
		inline Tile GetGridTile(uint32_t x, uint32_t y);				// returns a copy of the Tile at a localtion
	};

	// =========== Puplic =========== //
	inline bool BaseWorld::IsBiome(uint32_t x, uint32_t y, Nature::BiomeType t_biome)
	{
		Tile t = GetGridTile(x, y);
		Nature::Biome b;
		return (bool)t.GetBiome(t_biome, b);
	}

	inline void BaseWorld::SetBiome(uint32_t x, uint32_t y, unsigned int r, Nature::Biome b)
	{
		Nature::Biome* bPtr = &b;
		void* args = bPtr;
		OperateOnSphere(x, y, r, OperationAddBiome, args);
	}

	inline void BaseWorld::SetBiome(uint32_t x, uint32_t y, unsigned int r, Nature::BiomeType bType, int bMagnitude)
	{
		Nature::Biome b = Nature::Biome(bType, bMagnitude);
		SetBiome(x, y, r, b);
	}

	BaseWorld::BaseWorld(uint32_t width, uint32_t hight)
	{
		m_width = width;
		m_hight = hight;
		int length = m_width * m_hight;

		for (int i = 0; i < length; i++)
		{
			uint32_t x = i / m_width;
			uint32_t y = i % m_width;
			m_tileGrid.push_back(new Tile(x,y));
		}
	}

	BaseWorld::~BaseWorld()
	{
		m_tileGrid.clear();
	}

	inline BaseWorld::TileCache BaseWorld::BuildCache(Tile tile, unsigned int radius)
	{
		TileCache cache = TileCache();
		void* data[3];
		data[0] = &cache;
		data[1] = &tile.x;
		data[2] = &tile.y;
		void* args = data;
		OperateOnSphere(tile.x, tile.y, radius, OperationCacheTile, args);
		return TileCache();
	}

	inline Tile BaseWorld::GetGridTile(TileReference tileRef)
	{
		return GetGridTile(tileRef.x, tileRef.y);
	}

	// =========== Private =========== //
	inline Tile * BaseWorld::GetGridTilePtr(uint32_t x, uint32_t y)
	{
		int length = m_width* m_hight;
		int index = x * m_width + y;
		if (index >= length)
			throw;
		return (Tile*)m_tileGrid[index];
	}

	// =========== ======== =========== //
	// ======== Operations ======== //
	// =========== ======== =========== //
	void BaseWorld::OperateOnSphere
	(
		uint32_t x0, uint32_t y0, unsigned int & radius,
		void func(Tile* tile, void* args),
		void* args
	)
	{
		int r = radius;
		Tile* tilePtr = NULL;
		for (int x1 = x0 - r + 1; x1 < x0 + r; x1++)
		{
			for (int y1 = y0 - r + 1; y1 < y0 + r; y1++)
			{
				int dx = x0 - x1; // horizontal offset
				int dy = y0 - y1; // vertical offset
				if ((dx*dx + dy*dy) <= (r*r))
				{
					tilePtr = GetGridTilePtr(x1, y1);
					func(tilePtr, args);
				}
				tilePtr = NULL;
			}
		}
	}

	inline void BaseWorld::OperationAddBiome(Tile * tile, void* args)
	{
		Nature::Biome* b = (Nature::Biome*)args;
		tile->AddBiome(*b);
	}

	inline void BaseWorld::OperationCacheTile(Tile * tile, void * args)
	{
		void** data = &args;
		BaseWorld::TileCache* cache = (BaseWorld::TileCache*)data[0];
		uint32_t x = *(int*)data[1];
		uint32_t y = *(int*)data[2];
		TileReference* rTile = new TileReference(*tile, x, y);
		cache->push(*rTile);
	}

	// =========== Protected =========== //
	inline Tile BaseWorld::GetGridTile(uint32_t x, uint32_t y)
	{
		Tile* TilePtr = GetGridTilePtr(x, y);
		return *(new Tile(*TilePtr));
	}

}




