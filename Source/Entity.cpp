#include "Entity.h"

Entity::Entity(Position position, const unsigned int minerals, const unsigned int gas, const unsigned int dps) :
HasPosition(position), HasDPSUpgrade() {
  _minerals = minerals;
  _gas = gas;
  _dps = dps;
}

Entity::~Entity() {}

std::vector<Entity*>* Entity::neighborhood() const {
  std::vector<Entity*> *neighbors;
  //TODO
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
