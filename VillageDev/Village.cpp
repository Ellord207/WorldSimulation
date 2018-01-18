#include "stdafx.h"
#include "Village.h"

Village::Village() : 
	mPeasants(new std::vector<Peasant*>()) ,
	mBuildings(new std::vector<Building*>())
{

}

Village::~Village()
{
	mPeasants->clear();
	mBuildings->clear();
	delete mPeasants;
	delete mBuildings;
}

void Village::Initialize()
{
	
}