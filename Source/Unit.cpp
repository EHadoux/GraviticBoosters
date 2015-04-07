#include <cmath>
#include <sstream>
#include "Unit.h"

Unit::Unit(Position position, const unsigned int minerals, const unsigned int gas, const unsigned int dps, double xvelocity, double yvelocity) :
Entity(position, minerals, gas) {
  _xvelocity = xvelocity;
  _yvelocity = yvelocity;
}

Unit::~Unit() {}

double Unit::timeToPosition(Position to) {
  int deltax = abs((int)to.getX() - (int)getPosition().getX()), deltay = abs((int)to.getY() - (int)getPosition().getY());
  return sqrt(pow(deltax / _xvelocity, 2) + pow(deltay / _yvelocity, 2));
}

std::string Unit::toString() const {
  std::stringstream s;
  s << Entity::toString() << " with velocity " << _xvelocity << "," << _yvelocity;
  return s.str();
}

std::ostream& operator<< (std::ostream &stream, const Unit& unit) {
  return stream << unit.toString();
}