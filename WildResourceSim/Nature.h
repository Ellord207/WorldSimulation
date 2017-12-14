#pragma once

enum BiomeType
{
	Wasteland,
	Forest,
	Quarry,
	Plains,
	Mountains,
	Desert,
	Volcanic,
	Water,
};

struct Resources
{
	// food -> dependant for population
	int crops = 0;
	int wildlife = 0;
	int cattle = 0;

	// construction -> dependant for expantion
	int wood = 0;
	int stone = 0;

	// other -> movement and such
	int water = 0;
	int terrain = 0;
};

struct Biome
{
	Biome()
	{
		type = Wasteland;
		magnitude = 10;
	}
	BiomeType type;
	int magnitude;
};