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

void VillageManager::PeasantStatReport()
    {
    std::vector<Peasant*>* peasants = mVillage->mPeasants;
    std::cout << std::left << std::setw(15) << "First Name | " << std::setw(15) << "Last Name | " << std::setw(15) << "Health | " <<
        std::setw(15) << "Hunger | " << std::setw(15) << "Fatigue | " << std::setw(15) << "Status" << std::endl;
    std::cout << std::setfill('-') << std::setw(80) << " " << std::endl;
    std::cout << std::setfill(' ') << std::endl;

    
    for (int i = 0; i < peasants->size(); i++)
        {
        std::cout << std::setw(15) << peasants->at(i)->mFirstName << std::setw(15) << peasants->at(i)->mLastName << std::setw(15) <<
            peasants->at(i)->mHealth << std::setw(15) << peasants->at(i)->mHunger << std::setw(15) << peasants->at(i)->mFatigue <<
            (peasants->at(i)->IsDead() ? "Dead" : "Alive") << std::endl;
        }
    
    std::cout << std::endl;
    }