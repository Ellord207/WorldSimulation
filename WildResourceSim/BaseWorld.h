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
	bool isBiome(uint32_t x, uint32_t y, BiomeType biome);	// returns true, if the tile at the location has the give type of Biome
	BaseWorld(uint32_t width, uint32_t hight);
	~BaseWorld();

private:
	std::vector<Tile*> m_tileGrid;
	uint32_t m_width;
	uint32_t m_hight;

protected:
	Tile getGridTile(uint32_t x, uint32_t y);				// returns the Tile at a localtion  ?should this be a copy?  Another function???

};

inline bool BaseWorld::isBiome(uint32_t x, uint32_t y, BiomeType t_biome)
{
	Tile t = getGridTile(x, y);
	bool returnValue = false;
	Biome* biomesArray;
	int biomeCount;
	t.GetAllBiomes(biomesArray, biomeCount);

	for (int i = 0; i < biomeCount; i++)
	{
		if (biomesArray[i].type == t_biome)
			returnValue = true;
	}
	delete biomesArray;
	return returnValue;
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

inline Tile BaseWorld::getGridTile(uint32_t x, uint32_t y)
{
	int length = m_width* m_hight;
	int index = x * m_width + y;
	if (index >= length)
		throw;
	// should probably return a copy of this memory, but not right.
	return *m_tileGrid[index];
}
