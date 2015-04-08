#pragma once

#include <vector>
#include "Position.h"
#include "Entity.h"

class Tile {
public:
  Tile(unsigned int x, unsigned int y);
  ~Tile();

  double getPotential() const { return _potential; }
  void setPotential(double potential);

  std::vector<Entity*> getEntities() const;

private:
  double _potential;
};
