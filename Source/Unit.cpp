#include "Unit.h"
#include "GraviticBooster.h"
#include <cmath>
#include <algorithm>
#include <sstream>

Unit::Unit(const unsigned int id, Position position, const unsigned int minerals, const unsigned int gas, const double dpf,
           const double velocity, const unsigned int owner, const bool isWorker) :
           Entity(id, position, minerals, gas, dpf, owner) {
  _velocity = velocity;
  _isWorker = isWorker;
}

Unit::~Unit() {}

double Unit::economicPotential() const {
  return _isWorker ? MININGPOTENTIAL / (GraviticBooster::getClock() - getCreationTime()) : .0;
}

double Unit::aggressionPotential() const {
  std::cout << 1 - _position.euclidian(_closestEnemyPosition) / GraviticBooster::getMaxDistance() + (isAttacking() ? 0.5 : 0) << std::endl;
  return 1 - _position.euclidian(_closestEnemyPosition) / GraviticBooster::getMaxDistance() + (isAttacking() ? 0.5 : 0);
}

double Unit::strategicPotential() const {
  Entity *b = GraviticBooster::closestUnseenBuilding(_position, _owner);
  if(b == NULL) return 0;
  return 1 - _position.euclidian(b->getPosition()) / GraviticBooster::getMaxDistance();
}

double Unit::timeToPosition(Position to) const {
  int deltax = abs((int)to.getX() - (int)getPosition().getX()), deltay = abs((int)to.getY() - (int)getPosition().getY());
  return sqrt(pow(deltax / _velocity, 2) + pow(deltay / _velocity, 2));
}

std::vector<Unit*> Unit::unitNeighborhood() const {
  auto neighbors = neighborhood();
  auto uneighbors = std::vector<Unit*>();
  for(auto e : neighbors) {
    auto u = dynamic_cast<Unit*>(e);
    if(u) uneighbors.push_back(u);
  }
  return uneighbors;
}

std::string Unit::toString() const {
  std::stringstream s;
  s << Entity::toString() << " with velocity " << _velocity << " and dpf " << _dpf << " potential are: [" << aggressionPotential()
    << ", " << economicPotential() << ", " << strategicPotential() << "]";
  return s.str();
}

std::ostream& operator<< (std::ostream &stream, const Unit& unit) {
  return stream << unit.toString();
}
