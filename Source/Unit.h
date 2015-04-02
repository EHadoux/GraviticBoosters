#pragma once
#include "Entity.h"
#include "Position.h"
#include "HasTargetPosition.h"
#include "HasPopulation.h"
#include <vector>

class Unit : public Entity, HasTargetPosition, HasPopulation {
public:
  Unit(Position position, unsigned int minerals, unsigned int gas, unsigned int dps,
       double xvelocity, double yvelocity, unsigned int population);
  ~Unit();

  double timeToPosition(Position to) const;
  std::vector<Unit*>* unitNeighborhood() const;
  double aggressionPotential() const;

private:
  double _xvelocity, _yvelocity;
};
