#include <cmath>
#include <sstream>
#include "Unit.h"

Unit::Unit(Position position, const unsigned int minerals, const unsigned int gas, const double dpf, const double velocity) :
Entity(position, minerals, gas) {
  _velocity = velocity;
  _dpf = dpf;
}

Unit::~Unit() {}

double Unit::timeToPosition(Position to) {
  int deltax = abs((int)to.getX() - (int)getPosition().getX()), deltay = abs((int)to.getY() - (int)getPosition().getY());
  return sqrt(pow(deltax / _velocity, 2) + pow(deltay / _velocity, 2));
}

std::string Unit::toString() const {
  std::stringstream s;
  s << Entity::toString() << " with velocity " << _velocity << " and dpf " << _dpf;
  return s.str();
}

std::ostream& operator<< (std::ostream &stream, const Unit& unit) {
  return stream << unit.toString();
}