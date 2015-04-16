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
    tile->setPotentials(ap, ep, sp);
  }
  propagatePotential();
}

void Map::propagatePotential() {
  std::vector<std::tuple<double, double, double>> old(_tiles.size());
  std::transform(_tiles.begin(), _tiles.end(), old.begin(), [](Tile *t) {return t->getPotential(); });
  double dist, delta;
  for(unsigned int i = 0; i < _tiles.size(); ++i)
    if(std::get<0>(old[i]) > .0 || std::get<1>(old[i]) > .0 || std::get<2>(old[i]) > .0)
      for(unsigned int y = 0; y < _tiles.size(); ++y) {
        if(i == y)
          continue;
        dist = getPosition(i).euclidian(getPosition(y));
        if(dist < RADIUS) {
          delta = 1 + cos((dist / RADIUS)*PI) / 2;
          if(std::get<0>(old[i]) > .0) _tiles[y]->setAggressionPotential((_tiles[y]->getAggressionPotential() + std::get<0>(old[i]) * delta) / 2);
          if(std::get<1>(old[i]) > .0) _tiles[y]->setEconomicPotential((_tiles[y]->getEconomicPotential() + std::get<1>(old[i]) * delta) / 2);
          if(std::get<2>(old[i]) > .0) _tiles[y]->setStrategicPotential((_tiles[y]->getStrategicPotential() + std::get<2>(old[i]) * delta) / 2);
        }
      }
}