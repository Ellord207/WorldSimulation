#pragma once

#include <stdlib.h>
#include "Tile.h"
#include <vector>
#include <iterator>
#include <exception>

class BaseWorld
{
public:
	inline bool IsBiome(uint32_t x, uint32_t y, Nature::BiomeType biome);	// returns true, if the tile at the location has the give type of Biome
	inline void SetBiome(uint32_t x, uint32_t y, unsigned int r, Nature::Biome b);
	inline void SetBiome(uint32_t x, uint32_t y, unsigned int r, Nature::BiomeType bType, int bMagnitude);

	BaseWorld(uint32_t width, uint32_t hight);
	~BaseWorld();

private:
	std::vector<Tile*> m_tileGrid;
	uint32_t m_width;
	uint32_t m_hight;
	inline Tile* GetGridTilePtr(uint32_t x, uint32_t y);				// returns a Pointer to the Tile at a localtion

	// === Operations on Spheres === //
	inline void OperateOnSphere
	(
		uint32_t x, uint32_t y, unsigned int& radius,
		void func(Tile* tile, const void* args),
		const void* args
	);
	static inline void OperationAddBiome(Tile* tile, const void* args);

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
		m_tileGrid.push_back(new Tile());
}

BaseWorld::~BaseWorld()
{
	m_tileGrid.clear();
}

// =========== Private =========== //
inline Tile * BaseWorld::GetGridTilePtr(uint32_t x, uint32_t y)
{
	int length = m_width* m_hight;
	int index = x * m_width + y;
	if (index >= length)
		throw;
	return m_tileGrid[index];
}

// =========== ======== =========== //
  // ======== Operations ======== //
// =========== ======== =========== //
inline void BaseWorld::OperateOnSphere
(
	uint32_t x0, uint32_t y0, unsigned int & radius,
	void func(Tile* tile, const void* args),
	const void* args
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

inline void BaseWorld::OperationAddBiome(Tile * tile, const void* args)
{
	Nature::Biome* b = (Nature::Biome*)args;
	tile->AddBiome(*b);
}

// =========== Protected =========== //
inline Tile BaseWorld::GetGridTile(uint32_t x, uint32_t y)
{
	Tile* TilePtr = GetGridTilePtr(x, y);
	return *(new Tile(*TilePtr));
}


