#pragma once

#include "Tile.h"
#include "Entity.h"
#include <vector>

class Map {
public:
  Map(unsigned int width, unsigned int height, unsigned int tilew, unsigned int tileh);
  ~Map();

  unsigned int getWidth() const { return _width; }
  unsigned int getHeight() const { return _height; }

  Tile* getTileAt(unsigned int x, unsigned int y) const;
  Position* getPosition(unsigned int id) const;
  void update();

private:
  void propagatePotential();

  unsigned int _width, _height;
  std::vector<Tile*> _tiles;  
};
