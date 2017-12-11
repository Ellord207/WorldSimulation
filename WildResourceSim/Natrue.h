#pragma once


class NaturalResources
    {
    // resources 
    // crops, wildlife, cattle  : population
    // wood, stone              : contructions
    // water                    : A little bit everywhere
    // difficulty               : used for road generation later

    public:
        enum Biomes
            {
            Forest,
            Quarry,
            Plains,
            Mountains,
            Desert,
            Volcanic,
            Water
            };

        bool SetBiome(int x, int y, Biomes type, int r, int magnitude);
        int GetBiomes(int x, int y, Biomes*);
        NaturalResources();
        ~NaturalResources();

    private:

    };

NaturalResources::NaturalResources()
    {}

NaturalResources::~NaturalResources()
    {}