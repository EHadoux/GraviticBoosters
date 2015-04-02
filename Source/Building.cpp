#include "Building.h"
#include <algorithm>

Building::Building(Position position, const unsigned int minerals, const unsigned int gas, const unsigned int dps) :
Entity(position, minerals, gas, dps) {
  _seen = false;
}

Building::~Building() {}

std::vector<Building*>* Building::buildingNeighborhood() const {
  auto neighbors = neighborhood();
  auto bneighbors = new std::vector<Building*>();
  for(auto e : *neighbors) {
    auto b = dynamic_cast<Building*>(e);
    if(b) bneighbors->push_back(b);
  }
  return bneighbors;
}

double Building::aggressionPotential() const {
  // TODO
  return 0.0;
}