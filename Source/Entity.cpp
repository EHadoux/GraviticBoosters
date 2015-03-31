#include "Entity.h"

Entity::Entity(){
	// FIXME 
	//_gas = type.gasPrice();
	//_minerals = type.mineralPrice();
}

Entity::~Entity(){}

std::vector<Entity> Entity::neighborhood() {
	std::vector<Entity> neighbors;

	return neighbors;
}

double Entity::aggresssionPotential() {
	return 0.0;
}

double Entity::economicPotential() {
	return 0.0;
}

double Entity::strategicPotential() {
	return 0.0;
}

Position Entity::getPosition() const { return _position; }