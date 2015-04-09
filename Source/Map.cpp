#include "Map.h"
#include <algorithm>

#define PI 3.141592653
#define RADIUS 10

Map::Map(const unsigned int width, const unsigned int height, const unsigned int numOfTilesH, const unsigned int numOfTilesV) :
_tiles(numOfTilesH * numOfTilesV) {
  _width = width;
  _height = height;
  _numOfTilesH = numOfTilesH;
  _numOfTilesV = numOfTilesV;
  unsigned int tileH = _height / numOfTilesV, tileW = width / numOfTilesV;
  for(unsigned int x = 0; x < numOfTilesH; x++)
    for(unsigned int y = 0; y < numOfTilesV; y++)
      _tiles[y * numOfTilesV + x] = new Tile((tileW / 2) + x * tileW, (tileH / 2) + y * tileH, tileW, tileH);
}

Map::~Map() {
  for(auto t : _tiles)
    delete t;
}

Tile* Map::getTileAt(const unsigned int x, const unsigned int y) const {
  return _tiles[y * _numOfTilesV + x];
}

Position Map::getPosition(const unsigned int id) const {
  return Position(id % _numOfTilesV, id / _numOfTilesV);
}


void Map::update() {
  for(auto tile : _tiles) {
    auto entities = tile->getEntities();
    for(auto e : entities)
      tile->setPotential(tile->getPotential() + e->getPotential());
    tile->setPotential(tile->getPotential() / entities.size());
  }
  propagatePotential();
}

void Map::propagatePotential() {
  std::vector<double> old(_tiles.size());
  std::transform(_tiles.begin(), _tiles.end(), old.begin(), [](Tile *t) {return t->getPotential(); });
  Tile *neighbor;
  double dist;
  for(unsigned int i = 0; i < old.size(); ++i)
    for(unsigned int x = 0; x < _numOfTilesH; ++x)
      for(unsigned int y = 0; y < _numOfTilesV; ++y) {
        if(i == (y * _numOfTilesV + x))
          continue;
        neighbor = getTileAt(x, y);
        dist = getPosition(i).euclidian(getPosition(y * _numOfTilesV + x));
        if(dist < RADIUS)
          neighbor->setPotential((neighbor->getPotential() + old[i] * (1 + cos((dist / RADIUS)*PI) / 2)) / 2);
      }
}