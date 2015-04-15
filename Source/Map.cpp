#include "Map.h"
#include <algorithm>

#define PI 3.141592653
#define RADIUS 6

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

Tile* Map::getMaxTile() const {
  Tile * max = _tiles.front();
  for(auto tile : _tiles) {
    if(max->getPotential() < tile->getPotential())
      max = tile;
  }
  return max;
}

Position Map::getPosition(const unsigned int id) const {
  return Position(id % _numOfTilesH, id / _numOfTilesH);
}

void Map::update() {
  double ap = .0, ep = .0, sp = .0;
  for(auto tile : _tiles) {
    auto entities = tile->getEntities();
    if(entities.empty()) {
      tile->setAllPotentials(0.);
      continue;
    }
    for(auto e : entities) {
      ap += e->aggressionPotential();
      ep += e->economicPotential();
      sp += e->strategicPotential();
    }
    tile->setAggressionPotential(ap);
    tile->setEconomicPotential(ep);
    tile->setStrategicPotential(sp);
  }
  propagatePotential();
}

void Map::propagatePotential() {
  // TODO opti
  std::vector<double> oldA(_tiles.size());
  std::transform(_tiles.begin(), _tiles.end(), oldA.begin(), [](Tile *t) {return t->getAggressionPotential(); });
  std::vector<double> oldE(_tiles.size());
  std::transform(_tiles.begin(), _tiles.end(), oldE.begin(), [](Tile *t) {return t->getEconomicPotential(); });
  std::vector<double> oldS(_tiles.size());
  std::transform(_tiles.begin(), _tiles.end(), oldS.begin(), [](Tile *t) {return t->getStrategicPotential(); });
  double dist, delta;
  for(unsigned int i = 0; i < _tiles.size(); ++i)
    if(oldA[i] > .0 || oldE[i] > .0 || oldS[i] > .0)
      for(unsigned int y = 0; y < _tiles.size(); ++y) {
        if(i == y)
          continue;
        dist = getPosition(i).euclidian(getPosition(y));
        if(dist < RADIUS) {
          delta = 1 + cos((dist / RADIUS)*PI) / 2;
          if(oldA[i] > .0) _tiles[y]->setAggressionPotential((_tiles[y]->getAggressionPotential() + oldA[i] * delta) / 2);
          if(oldE[i] > .0) _tiles[y]->setEconomicPotential((_tiles[y]->getEconomicPotential() + oldE[i] * delta) / 2);
          if(oldS[i] > .0) _tiles[y]->setStrategicPotential((_tiles[y]->getStrategicPotential() + oldS[i] * delta) / 2);
        }
      }
}