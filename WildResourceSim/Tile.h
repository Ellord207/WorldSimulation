#pragma once

#include "stdafx.h"
#include "Nature.h"

class Tile
{
public:
	Tile();

	void AddBiome(Biome biome);  // * TODO * There can only be a single copy of a biome type in any given tile
	// I don't think this is a function I'll use in the game, but it will be nice to have.
	bool RemoveBiome(BiomeType biomeType);			// removes all biomes of the given type, if one is removed, returns true

	inline int GetBiomeCount();
	inline void GetAllBiomes(Biome*& biomes, int& biomeCount);	// returns all biomes in the tile
	inline bool GetBiome(BiomeType biomeType, Biome& biome); //returns true if a boime of that type, biomePtr will contain a pointer to the Biome

	~Tile();
private:
	int m_biomeCount;
	Biome* m_biomes;

	//Resources * TODO *
	//  Still haven't decided how this is going to go.
};



inline Tile::Tile()
{
	m_biomeCount = 0;
	m_biomes = new Biome[1];
}

inline void Tile::AddBiome(Biome biome)
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

bool Tile::RemoveBiome(BiomeType biomeType)
{
	int length = GetBiomeCount();
	bool retValue = false;

	for (int i = 0; i < length; i++)
	{
		if (m_biomes[i].type == biomeType)
		{
			retValue = true;
			size_t newSize = sizeof(Biome) * length - 1;
			Biome* temp = m_biomes;
			m_biomes = (Biome*)malloc(newSize);
			if (i > 0)
			{// copy first half of array
				size_t size = sizeof(Biome) * i;
				memcpy(m_biomes, temp, size);
			}
			if (i + 1 < length)
			{
				size_t size = sizeof(Biome) * (length - i - 1);
				memcpy(m_biomes + i, temp + i + 1, size);
			}
			delete temp;
			length--;
		}
	}

	return retValue;
}

inline int Tile::GetBiomeCount()
{
	int biomeCount = m_biomeCount;
	if (m_biomeCount == 0)
		biomeCount += 1;
	return biomeCount;

}

inline void Tile::GetAllBiomes(Biome *& biomes, int & biomeCount)
{
	size_t size = sizeof(Biome) * GetBiomeCount();
	biomes = (Biome*)malloc(size);
	memcpy(biomes, m_biomes, size);
	biomeCount = GetBiomeCount();
}

bool Tile::GetBiome(BiomeType biomeType, Biome& biome)
{
	biome.type = biomeType;
	biome.magnitude = 0;
	bool hasBiome = false;
	int length = GetBiomeCount();
	int biomeCounter = 0;
	for (int i = 0; i < length; i++)
	{
		if (m_biomes[i].type != biomeType)
			continue;
		hasBiome = true;
		biomeCounter++;
		biome.magnitude += m_biomes[i].magnitude;
	}
	// if there were multiple biomes. average there magnitudes, otherwise the magnitude is 0.
	biome.magnitude = hasBiome ? biome.magnitude / biomeCounter : 0;

	return hasBiome;
}

inline Tile::~Tile()
{
	delete m_biomes;
}