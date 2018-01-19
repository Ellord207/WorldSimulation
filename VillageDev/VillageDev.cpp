#include "stdafx.h"
#include "VillageManager.h"

int main()
{
	VillageManager manager;
	manager.Initialize();

    for (int i = 0; i < 32; i++)
        {
        manager.PeasantStatReport();
        manager.Tick();
        }

	return 0;
}

