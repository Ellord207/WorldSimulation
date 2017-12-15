#pragma once

#include <stdlib.h>
#include "Tile.h"
#include <vector>
#include <iterator>
#include <exception>

class BaseWorld
{
	// ------------------------------------------- //
	// 
	// ------------------------------------------- //


public:
	inline bool IsBiome(uint32_t x, uint32_t y, BiomeType biome);	// returns true, if the tile at the location has the give type of Biome


	BaseWorld(uint32_t width, uint32_t hight);
	~BaseWorld();

private:
	std::vector<Tile*> m_tileGrid;
	uint32_t m_width;
	uint32_t m_hight;

protected:
	inline Tile GetGridTile(uint32_t x, uint32_t y);				// returns a copy of the Tile at a localtion
	inline void GetGridTiles(uint32_t x, uint32_t y, unsigned int& radius, Tile*& tiles, int& tileCount);

};

inline bool BaseWorld::IsBiome(uint32_t x, uint32_t y, BiomeType t_biome)
{
	Tile t = GetGridTile(x, y);
	Biome b;
	return (bool)t.GetBiome(t_biome, b);
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

inline Tile BaseWorld::GetGridTile(uint32_t x, uint32_t y)
{
	int length = m_width* m_hight;
	int index = x * m_width + y;
	if (index >= length)
		throw;

	return *(new Tile(*m_tileGrid[index]));
}

inline void BaseWorld::GetGridTiles(uint32_t x, uint32_t y, unsigned int & radius, Tile *& tiles, int & tileCount)
{
	// needs to return an array of all the Tiles in a radius
	// equation for a circle: (x – h)^2 + (y – k)^2 = r^2
	// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
}
