#pragma once

#include <stdlib.h>
#include "Natrue.h"
#include <vector>
#include <iterator>
#include <exception>

class Tile
{
public:
	Tile()
	{
		m_biomeCount = 0;
		m_biomes = new Biome[1];
	}

	void AddBiome(Biome biome)
	{
		m_biomeCount++;
		if (m_biomeCount == 1)
		{
			m_biomes[0] = biome;
		}
		else
		{
			Biome* temp = m_biomes;
			m_biomes = new Biome[m_biomeCount];
			size_t size = sizeof(Biome) * (m_biomeCount - 1);
			memcpy(m_biomes, temp, size);
			delete temp;
		}
	}

	inline int GetBiomeCount()
	{
		int biomeCount = m_biomeCount;
		if (m_biomeCount == 0)
			biomeCount += 1;
		return biomeCount;
		
	}

	inline void GetBiomes(Biome*& biomes, int& biomeCount)
	{
		size_t size = sizeof(Biome) * GetBiomeCount();
		biomes = (Biome*)malloc(size);
		memcpy(biomes, m_biomes, size);
		biomeCount = GetBiomeCount();
	}

	~Tile()
	{
		delete m_biomes;
	}
private:
	int m_biomeCount;
	Biome* m_biomes;
};

class BaseWorld
{
	// ------------------------------------------- //
	// 
	// ------------------------------------------- //


public:
	bool isBiome(uint32_t x, uint32_t y, BiomeType biome);
	BaseWorld(uint32_t width, uint32_t hight);
	~BaseWorld();

private:
	std::vector<Tile*> m_tileGrid;
	uint32_t m_width;
	uint32_t m_hight;

protected:
	Tile getGridTile(uint32_t x, uint32_t y);

};


inline bool BaseWorld::isBiome(uint32_t x, uint32_t y, BiomeType t_biome)
{
	Tile t = getGridTile(x, y);
	bool returnValue = false;
	Biome* biomesArray;
	int biomeCount;
	t.GetBiomes(biomesArray, biomeCount);

	for (int i = 0; i < biomeCount; i++)
	{
		if (biomesArray[i].type == t_biome)
			returnValue = true;
	}

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
