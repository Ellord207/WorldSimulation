#pragma once


enum BiomeType
{
	Forest,
	Quarry,
	Plains,
	Mountains,
	Desert,
	Volcanic,
	Water,
	Road,
	Vilage
};

struct Biome
{
	BiomeType type;
	int magnitude;
};

class NaturalResources
    {
    // resources 
    // crops, wildlife, cattle  : population
    // wood, stone              : contructions
    // water                    : A little bit everywhere
    // difficulty               : used for road generation later

    public:

        bool SetBiome(int x, int y, BiomeType type, int r, int magnitude);
        int GetBiomes(int x, int y, BiomeType*);
        NaturalResources();
        ~NaturalResources();

    private:

    };

NaturalResources::NaturalResources()
    {}

NaturalResources::~NaturalResources()
    {}