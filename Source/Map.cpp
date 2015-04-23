#include "Map.h"
#include <algorithm>

#define PI 3.141592653
#define RADIUS 100

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

Tile* Map::getMaxSumTile() const {
  Tile * max = _tiles.front();
  for(auto tile : _tiles) {
    if(max->sumPotential() < tile->sumPotential())
      max = tile;
  }
  return max;
}

Tile* Map::getMaxTile() const {
  Tile * max = _tiles.front();
  for(auto tile : _tiles) {
    if(max->maxPotential() < tile->maxPotential())
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
    tile->setPotentials(ap / entities.size(), ep / entities.size(), sp / entities.size());
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

  /* CHANTIER
  int rs = ceil(RADIUS * 2.57);
  for(unsigned int i = 0; i < _numOfTilesH; i++)
    for(unsigned int j = 0; j < _numOfTilesV; j++) {
      double valAp = 0., valEp = 0., valSp = 0., wsum = 0.;
      for(unsigned int iy = i - rs; iy < i + rs + 1; iy++)
        for(unsigned int ix = j - rs; ix < j + rs + 1; ix++) {
          unsigned int x = fmin(_numOfTilesV - 1, fmax(0, ix));
          unsigned int y = fmin(_numOfTilesH - 1, fmax(0, iy));
          double dsq = (ix - j)*(ix - j) + (iy - i)*(iy - i);
          double wght = exp(-dsq / (2 * RADIUS*RADIUS)) / (PI * 2 * RADIUS*RADIUS);
          valAp += std::get<0>(old[y*_numOfTilesV + x]) * wght;
          valEp += std::get<1>(old[y*_numOfTilesV + x]) * wght;
          valSp += std::get<2>(old[y*_numOfTilesV + x]) * wght;
          wsum += wght;

          std::cout << wght << std::endl;
        }
      _tiles[i*_numOfTilesV + j]->setAggressionPotential(valAp / wsum);
      _tiles[i*_numOfTilesV + j]->setEconomicPotential(valEp / wsum);
      _tiles[i*_numOfTilesV + j]->setStrategicPotential(valSp / wsum);

    }
    */
}