#include "stdafx.h"
#include "Peasant.h"
#include "Constants.h"

Peasant::Peasant() : mHealth(10), mLevel(1), mHunger(100.0),
	mFatigue(100.0), mFirstName("Billy"), mLastName("Bob")
{

}

Peasant::~Peasant()
{

}

void Peasant::Initialize()
{

}

void Peasant::UpdateStats(int timePassed)
    {
    if (IsDead()) //no need for more calculations if we're dead
        return;

    for (int i = 0; i < timePassed; i++)
        {
        mHunger -= Constants::mPeasantHungerRate;
        mFatigue -= Constants::mPeasantFatigueRate;

        if (mHunger < 0)
            {
            mHealth--;
            mHunger = 0; //can't have negative hunger
            }

        if (mFatigue < 0)
            mFatigue = 0; //can't have negative fatigue, at least not when updating stats
        }
    }

bool Peasant::IsDead()
    {
    if (mHealth <= 0)
        return true;
    else
        return false;
    }