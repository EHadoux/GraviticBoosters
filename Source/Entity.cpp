#include "Entity.h"
#include <sstream>

Entity::Entity(int id, Position position, const unsigned int minerals, const unsigned int gas) :
_position(position) {
  _id = id;
  _minerals = minerals;
  _gas = gas;
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

std::string Entity::toString() const {
  std::stringstream s;
  s << "Entity at [" << _position.getX() << "," << _position.getY() << "] costs "
    << _minerals << " min and " << _gas << " gas";
  return s.str();
}

std::ostream& operator<< (std::ostream &stream, const Entity& unit) {
  return stream << unit.toString();
}