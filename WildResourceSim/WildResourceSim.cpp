// WildResourceSim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BaseWorld.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

#define COUT_FOR_TEST std::cout << std::left << std::setw(OUTWIDTH)

int main()
{
	const int OUTWIDTH = 25;
	// Yeah, I can't decide if I'm using C or C++.  Get over it.  At least there's no C# yet.

    printf("Welcome to Nature's resource sim.\n");

	World::BaseWorld world = World::BaseWorld(12, 12);
	world.SetBiome(5, 5, 2, Nature::Forest, 4);
	world.SetBiome(4, 4, 2, Nature::Mountains, 5);

	COUT_FOR_TEST << "There is Wasteland: " << world.IsBiome(1, 1, Nature::Wasteland) << std::endl;
	COUT_FOR_TEST << "There is NO Desert: " << !world.IsBiome(1, 1, Nature::Desert) << std::endl;

	COUT_FOR_TEST << "There is Forest: " << world.IsBiome(4, 4, Nature::Forest) << std::endl;
	COUT_FOR_TEST << "There is Mountains: " << world.IsBiome(4, 4, Nature::Mountains) << std::endl;
	COUT_FOR_TEST << "There is NO Wasteland: " << !world.IsBiome(4, 4, Nature::Wasteland) << std::endl;

	COUT_FOR_TEST << "There is Forest: " << world.IsBiome(5, 5, Nature::Forest) << std::endl;
	COUT_FOR_TEST << "There is Forest: " << world.IsBiome(6, 6, Nature::Forest) << std::endl;
	COUT_FOR_TEST << "There is NO Forest: " << !world.IsBiome(7, 7, Nature::Forest) << std::endl;

    //printf("Press enter to exit...");
    //scanf_s("poop");

    return 0;
}

