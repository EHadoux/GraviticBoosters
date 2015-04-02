#pragma once
#include "Tile.h"
#include <vector>

class Map {
public:
  Map(unsigned int w, unsigned int h);
  ~Map();

  unsigned int getWidth() const { return _width; }
  unsigned int getHeight() const { return _height; }

  Tile* getTileAt(unsigned int x, unsigned int y);

private:
  int _width, _height;
  std::vector<Tile*> _tiles;
};
