#pragma once
#include "BWAPI.h"
#include "Position.h"
#include <vector>

class Entity {
public:
	Entity();
	~Entity();
	Position getPosition() const;

	double aggresssionPotential();
	double economicPotential();
	double strategicPotential();

	std::vector<Entity> neighborhood();

private:
	Position _position;
	int _dps, _gas, _minerals;
};