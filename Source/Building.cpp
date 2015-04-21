#include "GraviticBooster.h"
#include "Building.h"
#include <algorithm>

Building::Building(const unsigned int id, Position position, const unsigned int minerals, const unsigned int gas,
                   const double dpf, const unsigned int owner, const bool isBase) :
                   Entity(id, position, minerals, gas, dpf, owner) {
  _seen = false;
  _isBase = isBase;
}

Building::~Building() {}

double Building::economicPotential() const {
  return _isBase ? (10.*MININGPOTENTIAL) / (GraviticBooster::getClock() - getCreationTime()) : .0;
}

std::vector<Building*> Building::buildingNeighborhood() const {
  auto neighbors = neighborhood();
  auto bneighbors = std::vector<Building*>();
  for(auto e : neighbors) {
    auto b = dynamic_cast<Building*>(e);
    if(b) bneighbors.push_back(b);
  }
  return bneighbors;
}
