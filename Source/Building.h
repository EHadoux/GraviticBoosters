#pragma once

#include "Entity.h"
#include <vector>

class Building : public Entity {
public:
  Building(unsigned int id, Position position, unsigned int minerals, unsigned int gas, double dpf, unsigned int owner, bool isBase);
  ~Building();

  bool seen() const { return _seen; }
  double economicPotential() const;
  void setVisibility(bool seen) { _seen = seen; }
  std::vector<Building*> buildingNeighborhood() const;
  bool isBase() const { return _isBase; }

private:
  bool _seen, _isBase;
};
