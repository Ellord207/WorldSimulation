#pragma once

class Peasant
{
public:
	Peasant();
	~Peasant();
	void Initialize();
    void UpdateStats(int timePassed);
    bool IsDead();

	int mHealth;
	int mLevel;
	float mHunger;
	float mFatigue;
	std::string mFirstName;
	std::string mLastName;

private:

};