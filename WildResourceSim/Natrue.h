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

class NaturalResources
    {
    // resources 
    // crops, wildlife, cattle  : population
    // wood, stone              : contructions
    // water                    : A little bit everywhere
    // difficulty               : used for road generation later

    public:

        NaturalResources();
        ~NaturalResources();

    private:

    };

NaturalResources::NaturalResources()
    {}

NaturalResources::~NaturalResources()
    {}