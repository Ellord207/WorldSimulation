#pragma once

#include "stdafx.h"
#include "Nature.h"

using namespace Nature;

class Tile
{
public:
	Tile();
	Tile(Tile& deepCopy);	// Creats a deep copy of the Tile passed in

	inline Tile DeepCopy(Tile deepCopy);			// Creats a deep copy of the Tile passed in

	void AddBiome(Biome biome);						// adds a new Biome, if autoFinalize is true, it will combine with any others of the same type.  Otherwise, it will exsist seperatly.
	bool RemoveBiome(BiomeType biomeType);			// removes all biomes of the given type, returns true if at least one is removed

	inline int GetBiomeCount();						// will return the number of biomes.  * Use this and do not just call for member varible *
	inline void GetAllBiomes(Biome*& biomes, int& biomeCount);	// returns all biomes in the tile
	inline int GetBiome(BiomeType biomeType, Biome& biome); //returns the count of the given type and "biome" will referense a biome of that type, the biome will contain a average of the Biomes Magnitude
	inline void ClearBiome();						// will remove all Biomes and assign it to be a wasteland.

	inline void FinalizeBiomes();  // makes sure there are only one of each Biome * sets autofinalize to true *
	inline bool IsFinalized();
	inline void SetAutoFinalize(bool autoFinalize);
	~Tile();

private:
	int m_biomeCount;
	Biome* m_biomes;
	bool f_finalized = false;
	bool f_autoFinalize = false;

	inline int GetBiomeCount(BiomeType type);
	//Resources * TODO *
	//  Still haven't decided how this is going to go.
};



inline Tile::Tile()
{
	ClearBiome();
}

inline Tile::Tile(Tile & t)
{
	m_biomeCount = t.m_biomeCount;
	f_autoFinalize = t.f_autoFinalize;
	f_finalized = t.f_finalized;
	
	int size = GetBiomeCount() * sizeof(Biome);
	m_biomes = (Biome*)malloc(size);
	memcpy(m_biomes, t.m_biomes, size);
}

inline Tile Tile::DeepCopy(Tile deepCopy)
{
	return Tile(deepCopy);
}

void Tile::AddBiome(Biome biome)
{
	f_finalized = false;
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
	if (f_autoFinalize)
		FinalizeBiomes();
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
			m_biomeCount--;
			if (m_biomeCount <= 0)
			{
				ClearBiome();
			}
			length--;
			if (f_finalized)
				break;
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

inline int Tile::GetBiome(BiomeType biomeType, Biome& biome)
{
	biome.type = biomeType;
	biome.magnitude = 0;
	int biomeCount = 0;
	int length = GetBiomeCount();
	int biomeCounter = 0;


	for (int i = 0; i < length; i++)
	{
		if (m_biomes[i].type != biomeType)
			continue;
		biomeCount++;
		biomeCounter++;
		biome.magnitude += m_biomes[i].magnitude;
	}
	// if there were multiple biomes. average there magnitudes, otherwise the magnitude is 0.
	biome.magnitude = biomeCount ? biome.magnitude / biomeCounter : 0;

	return biomeCount;
}

inline void Tile::ClearBiome()
{
	m_biomeCount = 0;
	delete m_biomes;
	m_biomes = new Biome[1];
	f_finalized = true;
	f_autoFinalize = false;
}

inline int Tile::GetBiomeCount(BiomeType biomeType)
{
	Biome b;
	return GetBiome(biomeType, b);
}

inline void Tile::FinalizeBiomes()
{
	if (f_finalized)
		return;  // No reason to do it again.

	int length = GetBiomeCount();
	Biome holdMyBiome;
	for (int i = 0; i < length; i++)
	{
		holdMyBiome.type = m_biomes[i].type;
		if (GetBiomeCount(holdMyBiome.type) <= 1)
			continue;
		GetBiome(holdMyBiome.type, holdMyBiome);
		RemoveBiome(holdMyBiome.type);
		AddBiome(holdMyBiome);
	}
	f_finalized = true;
	f_autoFinalize = true;
}

inline bool Tile::IsFinalized()
{
	return f_finalized;
}

inline void Tile::SetAutoFinalize(bool autoFinalize)
{
	f_autoFinalize = autoFinalize;
}

inline Tile::~Tile()
{
	delete m_biomes;
}
