#pragma once

#include <stdlib.h>
#include "Natrue.h"

class Tile
{
public:
	Tile(int attributeNum)
	{

	}



	~Tile()
	{

	}
private:
	Biome* m_attributes;
};

class BaseWorld
{
	// ------------------------------------------- //
	// 
	// ------------------------------------------- //


public:
	BaseWorld();
	~BaseWorld();

private:
	int m_nextAttId;


protected:
	// Each tile has a list of attributes, each time a new attribute is needed to be added, call this for a new id
	int GetAttributeId();
};


BaseWorld::BaseWorld()
{
	m_nextAttId = 0;

}

BaseWorld::~BaseWorld()
{}

inline int BaseWorld::GetAttributeId()
{
	return ++m_nextAttId;
}
