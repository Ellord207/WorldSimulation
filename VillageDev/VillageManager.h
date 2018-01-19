#pragma once
#include "Village.h"

class VillageManager
{
public:
	VillageManager();
	~VillageManager();
	void Initialize();
	void StartSimulation(int timeSpeed);
	void Tick();
    void PeasantStatReport();

	Village* mVillage;
	long int mTimeCount;
	int mTimeSpeed;
	float mHungerRate;
	float mFatigueRate;

private:

};