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

	BaseWorld world = BaseWorld(5, 12);

	std::cout << "Is there wasteland: " << world.isBiome(1, 1, Wasteland) << std::endl;

    printf("Press enter to exit...");
    scanf_s("poop");

    return 0;
}

