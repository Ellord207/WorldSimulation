#pragma once

#include "Peasant.h"
#include "Building.h"

class Village
{
public:
	Village();
	~Village();
	void Initialize();

	std::vector<Peasant*>* mPeasants;
	std::vector<Building*>* mBuildings;

private:

};