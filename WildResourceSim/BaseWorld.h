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
			int difference = distancex + distancey;
			double distance = std::round(sqrt(difference));
			return (int)distance;
		}
		bool operator<(const TileReference& right) const
		{
			return this->distance > right.distance;
		}
	};

	class BaseWorld
	{
	public:
		inline bool IsBiome(uint32_t x, uint32_t y, Nature::BiomeType biome);	// returns true, if the tile at the location has the give type of Biome
		inline void SetBiome(uint32_t x, uint32_t y, unsigned int r, Nature::Biome b);
		inline void SetBiome(uint32_t x, uint32_t y, unsigned int r, Nature::BiomeType bType, int bMagnitude);
		inline void FinalizeWorld();
		void Tick();

		BaseWorld(uint32_t width, uint32_t hight);
		~BaseWorld();

		// TileRefences in the Cache can use to get the actual Tiles from the world object  ------  Reference: http://en.cppreference.com/w/cpp/container/priority_queue
		typedef std::priority_queue<TileReference>TileCache;
		TileCache* BuildCache(Tile tile, unsigned int radius);
		TileCache* BuildCache(uint32_t x, uint32_t y, unsigned int radius);
		Tile* GetGridTile(TileReference tile);			//  Returns a deep copy of the tile
		
	private:
		struct CacheArg
		{
			int Orgin_x, Orgin_y;
			TileCache* Cache;
		};
		
		uint32_t m_width;
		uint32_t m_hight;
		inline Tile* GetGridTilePtr(uint32_t x, uint32_t y);				// returns a Pointer to the Tile at a localtion
		std::vector<Tile*> m_tileGrid;
																			// === Operations on Spheres === //
		void OperateOnSphere
		(
			uint32_t x, uint32_t y, unsigned int& radius,
			void func(Tile* tile, void* args),
			void* args
		);
		static inline void OperationAddBiome(Tile* tile, void* args);
		static inline void OperationCacheTile(Tile* tile, void* args);

	public: // protected:  // Change this and use a TileCache for the test.
		inline Tile* GetGridTile(uint32_t x, uint32_t y);				// returns a copy of the Tile at a localtion
	};

	// =========== Puplic =========== //
	inline bool BaseWorld::IsBiome(uint32_t x, uint32_t y, Nature::BiomeType t_biome)
	{
		Tile* t = GetGridTile(x, y);
		Nature::Biome b;
		return (bool)t->GetBiome(t_biome, b);
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

	inline void BaseWorld::FinalizeWorld()
	{
		// One way to interate through a vector.  For Each Funciton
		std::for_each(m_tileGrid.begin(), m_tileGrid.end(), [](Tile* x) {x->FinalizeBiomes(); });
	}

	inline void BaseWorld::Tick()
	{
		// One way to interate through a vector.  More like C# for(var i in collecion)
		for (auto const& it: m_tileGrid)
			it->TickResources();
		//std::for_each(m_tileGrid.begin(), m_tileGrid.end(), [](Tile* x) {x->TickResources(); });
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

	inline BaseWorld::TileCache* BaseWorld::BuildCache(uint32_t x, uint32_t y, unsigned int radius)
	{
		TileCache* cache = new TileCache();
		CacheArg* cacheArgs = new CacheArg();
		cacheArgs->Cache = cache;
		cacheArgs->Orgin_x = x;
		cacheArgs->Orgin_y = y;
		void* args = (void*)cacheArgs;
		OperateOnSphere(x, y, radius, OperationCacheTile, args);
		return cache;
	}

	inline BaseWorld::TileCache* BaseWorld::BuildCache(Tile tile, unsigned int radius)
	{
		return BuildCache(tile.x, tile.y, radius);
	}

	inline Tile* BaseWorld::GetGridTile(TileReference tileRef)
	{
		return GetGridTile(tileRef.x, tileRef.y);
	}

	// =========== Private =========== //
	inline Tile* BaseWorld::GetGridTilePtr(uint32_t x, uint32_t y)
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
		int leftBound = x0 - r + 1;
		int rightBound = x0 + r;
		int botBound = y0 - r + 1;
		int topBound = y0 + r;
		for (int x1 = leftBound; x1 < rightBound; x1++)
		{
			if (x1 < 0 || x1 >= m_width) continue;
			for (int y1 = botBound; y1 < topBound; y1++)
			{
				if (y1 < 0 || y1 >= m_hight) continue;
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

	inline void BaseWorld::OperationAddBiome(Tile* tile, void* args)
	{
		Nature::Biome* b = (Nature::Biome*)args;
		tile->AddBiome(*b);
	}

	inline void BaseWorld::OperationCacheTile(Tile* tile, void * args)
	{
		CacheArg* cacheArgs_ = (CacheArg*)args;
		BaseWorld::TileCache* cache = cacheArgs_->Cache;
		uint32_t x = cacheArgs_->Orgin_x;
		uint32_t y = cacheArgs_->Orgin_y;
		TileReference rTile = TileReference(*tile, x, y);
		cache->push(rTile);
	}

	// =========== Protected =========== //
	inline Tile* BaseWorld::GetGridTile(uint32_t x, uint32_t y)
	{
		Tile* TilePtr = GetGridTilePtr(x, y);
		//TilePtr = new Tile(*TilePtr);
		return TilePtr;
	}

}




