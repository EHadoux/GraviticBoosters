#include "Entity.h"
#include "GraviticBooster.h"
#include <sstream>

Entity::Entity(const unsigned int id, Position position, const unsigned int minerals, const unsigned int gas,
               const double dpf, const unsigned int owner) :
               _position(position), _closestEnemyPosition(0, 0) {
  _id = id;
  _minerals = minerals;
  _gas = gas;
  _owner = owner;
  _dpf = dpf;
  _creationTime = GraviticBooster::getClock();
}

Entity::~Entity() {}

std::vector<Entity*> Entity::neighborhood() const {
  std::vector<Entity*> neighbors;
  //TODO
  return neighbors;
}

double Entity::getPotential() const {
  double ap = aggressionPotential();
  double sp = strategicPotential();
  double ep = economicPotential();
  return fmax(ap, fmax(sp, ep));
}

double Entity::aggressionPotential() const {
  return .0;
}

double Entity::economicPotential() const {
  return .0;
}

double Entity::strategicPotential() const {
  return .0;
}

bool Entity::isEnnemy(const Entity &other) const {
  return _owner != other._owner;
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