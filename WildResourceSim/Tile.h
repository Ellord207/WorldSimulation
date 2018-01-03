#pragma once

#include "stdafx.h"
#include <stdint.h>
#include "Nature.h"

class Tile
{
public:
	uint32_t x, y;

	//   * TODO * make all this thread safe  ///
	Tile(uint32_t x, uint32_t y);
	Tile(Tile& deepCopy);	// Creats a deep copy of the Tile passed in

	void AddBiome(Nature::Biome biome);						// adds a new Biome, if autoFinalize is true, it will combine with any others of the same type.  Otherwise, it will exsist seperatly.
	bool RemoveBiome(Nature::BiomeType biomeType);			// removes all biomes of the given type, returns true if at least one is removed

	inline int GetBiomeCount();						// will return the number of biomes (takes into account for the default wasteland).  * Use this and do not just call for member varible *
	inline void GetAllBiomes(Nature::Biome*& biomes, int& biomeCount);	// returns all biomes in the tile
	inline int GetBiome(Nature::BiomeType biomeType, Nature::Biome& biome); //returns the count of the given type and "biome" will referense a biome of that type, the biome will contain a average of the Biomes Magnitude
	inline void ClearBiome();						// will remove all Biomes and assign it to be a wasteland.

	inline void FinalizeBiomes();  // makes sure there are only one of each Biome *sets autofinalize to true*
	inline bool IsFinalized();
	inline void SetAutoFinalize(bool autoFinalize);

	//  These only reference the orignal Tile  Yeah, this is a bit janky
	inline Nature::Resources AvailableResources();				// returns a deep copy of the available resources 
	inline int Tile::AvailableResources(Nature::Resources::ResourceTypes type);
	inline int Tile::RequestResources(Nature::Resources::ResourceTypes type, int amount); // takes an order for resources and will hand back the resources that could be filled by the order.  Will return ture if the order was filled.

	~Tile();

private:
	int m_biomeCount;			// Number of biomes present ( does not include the defualt wasteland )
	Nature::Biome* m_biomes;	// List of biomes present
	Tile* m_orignalTile;		// used to reference the orignal tile for resources and such
	bool f_finalized = false;
	bool f_autoFinalize = false;
	const int MAX_BIOME_MAG = 100;

	inline int GetBiomeCount(Nature::BiomeType type);

	class
	{
	public:
		inline void ClearResourceStorage()
		{
			for (int i = 0; i < ResType::NUMBER_OF_TYPES; i++)
			{
				m_resourcesArray[i] = 0;
			}
		}

		inline Nature::Resources PeekResourcesStruct()
		{
			Nature::Resources r = Nature::Resources();
			r.cattle = PeekResource(ResType::Cattle);
			r.crops = PeekResource(ResType::Crops);
			r.stone = PeekResource(ResType::Stone);
			r.terrain = PeekResource(ResType::Terrain);
			r.water = PeekResource(ResType::Water);
			r.wildlife = PeekResource(ResType::Wildlife);
			r.wood = PeekResource(ResType::Wood);
			return r;
		}
		inline int PeekResource(Nature::Resources::ResourceTypes type)
		{
			return m_resourcesArray[type];
		}
		inline void SetResource(Nature::Resources::ResourceTypes type, int value)
		{
			m_resourcesArray[type] = value;
		}
		// This is not currently the final function
		void CalculateResources(Nature::Biome biome)
		{
			int previousResources[ResType::NUMBER_OF_TYPES];

			// Do I need this to persist betweem biomes and other
			for (int i = 0; i < ResType::NUMBER_OF_TYPES; i++)
				previousResources[i] = m_resourcesArray[i];;

			typedef Nature::BiomeType BType;
			switch (biome.type)
			{
			case BType::Forest:

				break;
			case BType::Quarry:

				break;
			case BType::Plains:

				break;
			case BType::Mountains:

				break;
			case BType::Desert:

				break;
			case BType::Volcanic:

				break;
			case BType::Water:

				break;
			case BType::Wasteland:
			default:
				break;
			}
		}

	private:
		typedef Nature::Resources::ResourceTypes ResType;
		int m_resourcesArray[ResType::NUMBER_OF_TYPES];
	}m_resources;
};

inline Tile::Tile(uint32_t x, uint32_t y)
{
	this->x = x;
	this->y = y;
	this->m_orignalTile = this;
	ClearBiome();
	m_resources.ClearResourceStorage();
}

inline Tile::Tile(Tile & t)
{
	m_biomeCount = t.m_biomeCount;
	f_autoFinalize = t.f_autoFinalize;
	f_finalized = t.f_finalized;
	m_orignalTile = t.m_orignalTile;

	int size = GetBiomeCount() * sizeof(Nature::Biome);
	m_biomes = (Nature::Biome*)malloc(size);
	memcpy(m_biomes, t.m_biomes, size);
}

void Tile::AddBiome(Nature::Biome biome)
{
	f_finalized = false;
	m_biomeCount++;
	if (m_biomeCount == 1)
	{
		m_biomes[0] = biome;
	}
	else
	{
		Nature::Biome* temp = m_biomes;
		m_biomes = new Nature::Biome[m_biomeCount];
		size_t size = sizeof(Nature::Biome) * (m_biomeCount - 1);
		memcpy(m_biomes + 1, temp, size);
		m_biomes[0] = biome;
		delete temp;
	}
	if (f_autoFinalize)
		FinalizeBiomes();
}

bool Tile::RemoveBiome(Nature::BiomeType biomeType)
{
	int length = GetBiomeCount();
	bool retValue = false;

	for (int i = 0; i < length; i++)
	{
		if (m_biomes[i].type == biomeType)
		{
			retValue = true;
			size_t newSize = sizeof(Nature::Biome) * length - 1;
			Nature::Biome* temp = m_biomes;
			//m_biomes = (Nature::Biome*)malloc(newSize);
			m_biomes = new Nature::Biome[length - 1];
			if (i > 0)
			{// copy first half of array
				size_t size = sizeof(Nature::Biome) * i;
				memcpy(m_biomes, temp, size);
			}
			if (i + 1 < length)
			{
				size_t size = sizeof(Nature::Biome) * (length - i - 1);
				memcpy(m_biomes + i, temp + i + 1, size);
			}
			delete temp;
			m_biomeCount--;
			if (m_biomeCount <= 0)
			{
				ClearBiome();
			}
			length--;
			i--;
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
		biomeCount = 1;
	return biomeCount;

}

inline void Tile::GetAllBiomes(Nature::Biome *& biomes, int & biomeCount)
{
	size_t size = sizeof(Nature::Biome) * GetBiomeCount();
	biomes = (Nature::Biome*)malloc(size);
	memcpy(biomes, m_biomes, size);
	biomeCount = GetBiomeCount();
}

inline int Tile::GetBiome(Nature::BiomeType biomeType, Nature::Biome& biome)
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
	biome.magnitude = (float)biomeCount ? biome.magnitude / (float)biomeCounter : 0;

	return biomeCount;
}

inline void Tile::ClearBiome()
{
	m_biomeCount = 0;
	delete m_biomes;
	m_biomes = new Nature::Biome[1];
	f_finalized = true;
	f_autoFinalize = false;
}

inline int Tile::GetBiomeCount(Nature::BiomeType biomeType)
{
	Nature::Biome b;
	return GetBiome(biomeType, b);
}

inline void Tile::FinalizeBiomes()
{
	if (f_finalized)
		return;  // No reason to do it again.

	//Combine Biomes
	int length = GetBiomeCount();
	Nature::Biome holdMyBiome;
	for (int i = 0; i < length; i++)
	{
		holdMyBiome.type = m_biomes[i].type;
		if (GetBiomeCount(holdMyBiome.type) <= 1)
			continue;
		GetBiome(holdMyBiome.type, holdMyBiome);
		RemoveBiome(holdMyBiome.type);
		AddBiome(holdMyBiome);
		length = GetBiomeCount();
	}

	//Balance Biome Magnitutes
	float totalMagnitude = 0;
	for (int i = 0; i < length; i++)
		totalMagnitude += m_biomes[i].magnitude;
	if (totalMagnitude > MAX_BIOME_MAG)
	{
		for (int i = 0; i < length; i++)
			m_biomes[i].magnitude = (m_biomes[i].magnitude/totalMagnitude)*(float)MAX_BIOME_MAG;
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

inline Nature::Resources Tile::AvailableResources()
{
	return  m_orignalTile->m_resources.PeekResourcesStruct();
}

inline int Tile::AvailableResources(Nature::Resources::ResourceTypes type)
{
	return  m_orignalTile->m_resources.PeekResource(type);
}

inline int Tile::RequestResources(Nature::Resources::ResourceTypes type, int amount)
{
	int resource = m_orignalTile->m_resources.PeekResource(type);
	int resourceRemaining = resource - amount;
	if (resourceRemaining < 0)
	{
		amount = resource;
		resourceRemaining = 0;
	}
	m_orignalTile->m_resources.SetResource(type, resourceRemaining);

	return amount;
}

inline Tile::~Tile()
{
	delete m_biomes;
}
