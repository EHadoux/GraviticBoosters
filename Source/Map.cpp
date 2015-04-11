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
  unsigned int tileH = _height / numOfTilesV, tileW = width / numOfTilesH;
  for(unsigned int x = 0; x < numOfTilesH; x++)
    for(unsigned int y = 0; y < numOfTilesV; y++)
      _tiles[y * numOfTilesH + x] = new Tile((tileW / 2) + x * tileW, (tileH / 2) + y * tileH, tileW, tileH);
}

Map::~Map() {
  for(auto t : _tiles)
    delete t;
}

Tile* Map::getTileAt(const unsigned int x, const unsigned int y) const {
  return _tiles[y * _numOfTilesH + x];
}

Position Map::getPosition(const unsigned int id) const {
  return Position(id % _numOfTilesH, id / _numOfTilesH);
}


void Map::update() {
  double potential = .0;
  for(auto tile : _tiles) {
    tile->setPotential(.0);
    auto entities = tile->getEntities();
    if(entities.empty())
      continue;
    for(auto e : entities)
      potential += e->getPotential();
    tile->setPotential(potential / entities.size());
  }
  propagatePotential();
}

void Map::propagatePotential() {
  std::vector<double> old(_tiles.size());
  std::transform(_tiles.begin(), _tiles.end(), old.begin(), [](Tile *t) {return t->getPotential(); });
  double dist;
  for(unsigned int i = 0; i < old.size(); ++i)
    for(unsigned int y = 0; y < old.size(); ++y) {
      if(i == y || old[i] == .0)
        continue;
      dist = getPosition(i).euclidian(getPosition(y));
      if(dist < RADIUS)
        //_tiles[y]->setPotential(fmax(old[y], old[i] * (1 + cos((dist / RADIUS)*PI) / 2)));
        _tiles[y]->setPotential(fmax(old[y], old[i] * 1 - (dist / RADIUS)));
    }
}