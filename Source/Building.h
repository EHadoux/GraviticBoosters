#pragma once

#include "Entity.h"
#include <vector>

class Building : public Entity {
public:
  Building(unsigned int id, Position position, unsigned int minerals, unsigned int gas, double dpf, unsigned int owner);
  ~Building();

  bool seen() const { return _seen; }
  void setVisibility(bool seen) { _seen = seen; }
  std::vector<Building*> buildingNeighborhood() const;

private:
  bool _seen;
};
