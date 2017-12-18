// WildResourceSim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BaseWorld.h"
#include <string.h>
#include <stdio.h>
#include <iostream>

int main()
{
	// Yeah, I can't decide if I'm using C or C++.  Get over it.  At least there's no C# yet.

    printf("Welcome to Nature's resource sim.\n");

	BaseWorld world = BaseWorld(12, 12);
	world.SetBiome(5, 5, 2, Nature::Forest, 4);

	std::cout << "Is there wasteland: " << world.IsBiome(1, 1, Nature::Wasteland) << std::endl;	//true 1
	std::cout << "Is there Desert: " << world.IsBiome(1, 1, Nature::Desert) << std::endl;		//false 0
	std::cout << "Is there Forest: " << world.IsBiome(4, 4, Nature::Forest) << std::endl;		//true 1
	std::cout << "Is there wasteland: " << world.IsBiome(5, 5, Nature::Wasteland) << std::endl;	//false 0
	std::cout << "Is there Forest: " << world.IsBiome(5, 5, Nature::Forest) << std::endl;		//true 1
	std::cout << "Is there Forest: " << world.IsBiome(6, 6, Nature::Forest) << std::endl;		//true 1
	std::cout << "Is there Forest: " << world.IsBiome(7, 7, Nature::Forest) << std::endl;		//false 0

    //printf("Press enter to exit...");
    //scanf_s("poop");

    return 0;
}

