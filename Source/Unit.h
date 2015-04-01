#pragma once
#include "Entity.h"
#include "Position.h"

class Unit : public Entity
{
public:
	Unit(Position position, unsigned int minerals, unsigned int gas, unsigned int dps, double xvelocity, double yvelocity);
	~Unit();
	double timeToPosition(Position to);
	
private:
	double _xvelocity, _yvelocity;
};
