#pragma once

#include "Tile.h"
#include "Entity.h"
#include <vector>
#include <tuple>

class Map {
public:
  Map(unsigned int width, unsigned int height, unsigned int numOfTilesH, unsigned int numOfTilesV);
  ~Map();

  unsigned int getWidth() const { return _width; }
  unsigned int getHeight() const { return _height; }
  unsigned int getNumOfTilesH() const { return _numOfTilesH; }
  unsigned int getNumOfTilesV() const { return _numOfTilesV; }

  Tile* getTileAt(unsigned int x, unsigned int y) const;
  Tile* getMaxTile() const;
  Tile* getMaxSumTile() const;
  Position getPosition(unsigned int id) const;
  void update();

private:
  void propagatePotential();

  unsigned int _width, _height, _numOfTilesH, _numOfTilesV;
  std::vector<Tile*> _tiles;  
};
