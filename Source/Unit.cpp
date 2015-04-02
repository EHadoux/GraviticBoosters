#include "Unit.h"
#include <cmath>
#include <algorithm>

Unit::Unit(Position position, const unsigned int minerals, const unsigned int gas, const unsigned int dps,
           const double xvelocity, const double yvelocity, unsigned int population) :
           Entity(position, minerals, gas, dps), HasTargetPosition(), HasPopulation(population) {
  _xvelocity = xvelocity;
  _yvelocity = yvelocity;
}

Unit::~Unit() {}

double Unit::timeToPosition(Position to) {
  int deltax = abs((int)to.getX() - (int)getPosition().getX()), deltay = abs((int)to.getY() - (int)getPosition().getY());
  return sqrt(pow(deltax / _xvelocity, 2) + pow(deltay / _yvelocity, 2));
}

std::vector<Unit*>* Unit::unitNeighborhood() const {
  auto neighbors = neighborhood();
  auto uneighbors = new std::vector<Unit*>();
  for(auto e : *neighbors) {
    auto u = dynamic_cast<Unit*>(e);
    if(u) uneighbors->push_back(u);
  }
  return uneighbors;
}