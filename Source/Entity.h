#pragma once
#include "Position.h"
#include <vector>

class Entity {
public:
	Entity(Position position, int minerals, int gas, int dps);
	~Entity();

	Position getPosition() const { return _position; }

	double aggressionPotential() const;
	double economicPotential() const;
	double strategicPotential() const;

	std::vector<Entity*> neighborhood();

private:
	Position _position;
	int _dps, _gas, _minerals;
};
