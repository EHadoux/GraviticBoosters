#pragma once

#include "Entity.h"
#include <vector>

class Building : public Entity {
public:
  Building(Position position, unsigned int minerals, unsigned int gas, unsigned int dps);
  ~Building();

  bool getVisibility() const { return _seen; }
  void setVisibility(bool seen) { _seen = seen; }
  std::vector<Building*> buildingNeighborhood() const;
  double aggressionPotential() const;

private:
  bool _seen;
};
