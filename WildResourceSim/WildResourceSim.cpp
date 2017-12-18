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
	world.SetBiome(5, 5, 2, Forest, 4);

	std::cout << "Is there wasteland: " << world.IsBiome(1, 1, Wasteland) << std::endl;	//true
	std::cout << "Is there Desert: " << world.IsBiome(1, 1, Desert) << std::endl;		//false
	std::cout << "Is there Forest: " << world.IsBiome(4, 4, Forest) << std::endl;		//true
	std::cout << "Is there wasteland: " << world.IsBiome(5, 5, Wasteland) << std::endl;	//false
	std::cout << "Is there Forest: " << world.IsBiome(5, 5, Forest) << std::endl;		//true
	std::cout << "Is there Forest: " << world.IsBiome(6, 6, Forest) << std::endl;		//true
	std::cout << "Is there Forest: " << world.IsBiome(7, 7, Forest) << std::endl;		//false

    //printf("Press enter to exit...");
    //scanf_s("poop");

    return 0;
}

