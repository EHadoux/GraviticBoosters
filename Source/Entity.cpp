#include "Entity.h"

Entity::Entity(Position position, const unsigned int minerals,
               const unsigned int gas, const unsigned int dps) :
_position(position) {
	_minerals = minerals;
	_gas      = gas;
	_dps      = dps;
}

Entity::~Entity() {}

std::vector<Entity*> Entity::neighborhood() {
	std::vector<Entity*> neighbors;

	return neighbors;
}

double Entity::aggressionPotential() const {
	return 0.0;
}

double Entity::economicPotential() const {
	return 0.0;
}

double Entity::strategicPotential() const {
	return 0.0;
}
