#include "stdafx.h"
#include "VillageManager.h"

int main()
{
	VillageManager manager;
	manager.Initialize();
	Peasant* test = manager.mVillage->mPeasants->at(9);
	test->mFirstName.clear();
	test->mFirstName.assign("Frank");

	for (int i = 0; i < manager.mVillage->mPeasants->size(); i++)
	{
		std::cout << manager.mVillage->mPeasants->at(i)->mFirstName << ", ";
	}

	std::cout << "Name of last peasant in list: " << manager.mVillage->mPeasants->at(9)->mFirstName << std::endl;
	std::cout << "Name of removed peasant: " << test->mFirstName << std::endl;
    delete manager.mVillage->mPeasants->at(9);
    manager.mVillage->mPeasants->pop_back();
	std::cout << "Name of removed peasant: " << test->mFirstName << std::endl;

	for (int i = 0; i < manager.mVillage->mPeasants->size(); i++)
	{
		std::cout << manager.mVillage->mPeasants->at(i)->mFirstName << ", ";
	}
	system("pause");
	return 0;
}

