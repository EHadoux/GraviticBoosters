#include <cmath>
#include "Unit.h"

Unit::Unit(Position position, const unsigned int minerals, const unsigned int gas, const unsigned int dps,
           const double xvelocity, const double yvelocity, unsigned int population) :
           Entity(position, minerals, gas), HasTargetPosition(), HasPopulation(population) {
	_xvelocity = xvelocity;
	_yvelocity = yvelocity;
}

Unit::~Unit() {}

double Unit::timeToPosition(Position to) {
  int deltax = abs((int)to.getX() - (int)getPosition().getX()), deltay = abs((int)to.getY() - (int)getPosition().getY());
  return sqrt(pow(deltax / _xvelocity, 2) + pow(deltay / _yvelocity, 2));
}
