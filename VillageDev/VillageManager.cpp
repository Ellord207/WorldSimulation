#include "stdafx.h"
#include "VillageManager.h"


VillageManager::VillageManager() :
	mVillage(new Village()),
	mTimeCount(0), mTimeSpeed(1),
	mHungerRate(5), mFatigueRate(1)
{

}

VillageManager::~VillageManager()
{
	delete mVillage;
}

void VillageManager::Initialize()
{
	for (int i = 0; i < 10; i++)
		mVillage->mPeasants->push_back(new Peasant());
	for (int i = 0; i < 5; i++)
		mVillage->mBuildings->push_back(new Building());
}

void VillageManager::StartSimulation(int timeSpeed)
{
	mTimeSpeed = timeSpeed;
	Initialize();
}

void VillageManager::Tick()
{
	//loop through all peasants and subtract hunger and fatigue
	for (int i = 0; i < mVillage->mPeasants->size(); i++)
	{
        mVillage->mPeasants->at(i)->UpdateStats(mTimeSpeed);

		//check to see if peasants have died
        //if (mVillage->mPeasants->at(i)->IsDead())

	}
}

void VillageManager::PeasantStatReport(Peasant* peasant)
    {

    }