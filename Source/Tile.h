#pragma once

#include <vector>
#include "Position.h"
#include "Entity.h"

class Tile {
public:
  Tile(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
  ~Tile();

  double getPotential() const { return _potential; }
  void setPotential(double potential);
  Position getCenterPosition() const { return _centerPos; }
  std::vector<Entity*> getEntities() const;

private:
  Position _centerPos;
  double _potential;
  int _width, _height;
};
