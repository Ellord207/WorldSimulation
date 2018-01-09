// WildResourceSim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BaseWorld.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

#define COUT_FOR_TEST std::cout << std::left << std::setw(OUTWIDTH)
#define COUT_BAR std::cout << std::left << std::setw(OUTWIDTH/2) << "----------------------"

int main()
{
	const int OUTWIDTH = 40;
	Nature::Biome overlappingForest, singleForest, singleMount;
	float forst1Mag = 40, forst2Mag = 30, mount1Mag = 50, desert1Mag = 40;

	// Yeah, I can't decide if I'm using C or C++.  Get over it.  At least there's no C# yet.
    printf("Welcome to Nature's resource sim.\n");
	COUT_FOR_TEST << " - Test Description - " << "Test output" << std::endl;

	// Basic functionality Tests
	World::BaseWorld world = World::BaseWorld(8, 8);
	world.SetBiome(5, 5, 2, Nature::Forest, forst1Mag);
	world.SetBiome(4, 4, 3, Nature::Mountains, mount1Mag);
	world.SetBiome(3, 7, 2, Nature::Forest, forst2Mag);
	world.SetBiome(4, 6, 1, Nature::Desert, desert1Mag);

	Tile* tPtr = world.GetGridTile(4, 6);

	COUT_BAR << "World Unfinalized" << std::endl;
	COUT_FOR_TEST << "Is world NOT finalized: " << !world.GetGridTile(4, 6)->IsFinalized() << std::endl;
	
	//Multiple biomes Test
	COUT_FOR_TEST << "There is Overlaped Forest: " << (2 == world.GetGridTile(4, 6)->GetBiome(Nature::Forest, overlappingForest)) << std::endl;
	COUT_FOR_TEST << "There is Forest: " << world.GetGridTile(4, 4)->GetBiome(Nature::Forest, singleForest) << std::endl;
	COUT_FOR_TEST << "There is Mountains: " << world.GetGridTile(4, 4)->GetBiome(Nature::Mountains, singleMount) << std::endl;
	COUT_FOR_TEST << "There is NO Wasteland: " << !world.IsBiome(4, 4, Nature::Wasteland) << std::endl;

	//Magnitude Test
	COUT_FOR_TEST << "Mag Overlaped Forest: " <<((forst1Mag + forst2Mag)/2.00 == overlappingForest.magnitude) << std::endl;
	COUT_FOR_TEST << "Mag Forest correct: " << (forst1Mag == singleForest.magnitude) << std::endl;
	COUT_FOR_TEST << "Mag Mountains correct: " << (mount1Mag == singleMount.magnitude) << std::endl;

	world.FinalizeWorld();
	COUT_BAR << "World Finalized" << std::endl;

	COUT_FOR_TEST << "Is world finalized: " << world.GetGridTile(4, 6)->IsFinalized() << std::endl;

	// Default Biome Test
	COUT_FOR_TEST << "There is Wasteland: " << world.IsBiome(1, 1, Nature::Wasteland) << std::endl;
	COUT_FOR_TEST << "There is NO Desert: " << !world.IsBiome(1, 1, Nature::Desert) << std::endl;

	//Multiple biomes Test
	COUT_FOR_TEST << "There is Overlaped Forest: " << world.GetGridTile(4, 6)->GetBiome(Nature::Forest, overlappingForest) << std::endl;
	COUT_FOR_TEST << "There is Forest: " << world.GetGridTile(4, 4)->GetBiome(Nature::Forest, singleForest)  << std::endl;
	COUT_FOR_TEST << "There is Mountains: " << world.GetGridTile(4, 4)->GetBiome(Nature::Mountains, singleMount) << std::endl;
	COUT_FOR_TEST << "There is NO Wasteland: " << !world.IsBiome(4, 4, Nature::Wasteland) << std::endl;

	//Magnitude Test
	float combMag = ((forst1Mag + forst2Mag) / 2) / (((forst1Mag + forst2Mag) / 2.00) + mount1Mag + desert1Mag) * 100.00;
	COUT_FOR_TEST << "Mag Overlaped Forest: " << (combMag == overlappingForest.magnitude) << std::endl;
	COUT_FOR_TEST << "Mag Forest correct: " << (forst1Mag == singleForest.magnitude) << std::endl;
	COUT_FOR_TEST << "Mag Mountains correct: " << (mount1Mag == singleMount.magnitude) << std::endl;

	//Radius test
	COUT_FOR_TEST << "There is Forest: " << world.IsBiome(5, 5, Nature::Forest) << std::endl;
	COUT_FOR_TEST << "There is Forest: " << world.IsBiome(6, 6, Nature::Forest) << std::endl;
	COUT_FOR_TEST << "There is NO Forest: " << !world.IsBiome(7, 7, Nature::Forest) << std::endl;
	COUT_BAR << "End of Tests\n" << std::endl;
    //printf("Press enter to exit...");
    //scanf_s("poop");

	world.Tick();
	world.BuildCache(3, 6, 3);

    World::BaseWorld MassiveTest = World::BaseWorld(500, 500);

    return 0;
}

#undef COUT_FOR_TEST

