#include "Map.h"
#include <algorithm>

#define PI 3.141592653
#define RADIUS 4

Map::Map(const unsigned int width, const unsigned int height, const unsigned int numOfTilesH, const unsigned int numOfTilesV) :
_tiles(numOfTilesH * numOfTilesV) {
  _width = width;
  _height = height;
  _numOfTilesH = numOfTilesH;
  _numOfTilesV = numOfTilesV;
  unsigned int tileH = _height / numOfTilesV, tileW = width / numOfTilesH;
  int i = 0;
  for(unsigned int x = 0; x < numOfTilesH; x++)
    for(unsigned int y = 0; y < numOfTilesV; y++)
      _tiles[y * numOfTilesH + x] = new Tile((tileW / 2) + x * tileW, (tileH / 2) + y * tileH, tileW, tileH, ++i);
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
    sp = .0;
    for(auto e : entities) {
      ap += e->aggressionPotential(); ep += e->economicPotential(); 
      if(sp < e->strategicPotential() )
        sp = e->strategicPotential();
    }
    ap /= entities.size(); ep /= entities.size(); //sp /= entities.size();
    tile->setPotentials(ap, ep, sp);
  }  
  propagatePotential();
  /*
  for(auto tile : _tiles)
    tile->isRelevantPotentialPoint();
  */
}

void Map::propagatePotential() {
  std::vector<std::tuple<double, double, double>> old(_tiles.size());
  std::transform(_tiles.begin(), _tiles.end(), old.begin(), [](Tile *t) {return t->getPotential(); });
  double dist, wght, valAp, valEp, valSp, wsum;
  for(unsigned int i = 0; i < _tiles.size(); ++i) {
    valAp = 0., valEp = 0., valSp = 0., wsum = 0.;
    for(unsigned int j = 0; j < _tiles.size(); ++j) {
     dist = sqrt(pow((double)(i % _numOfTilesH) - (double)(j % _numOfTilesH), 2) + pow((double)(i / _numOfTilesH) - (double)(j / _numOfTilesH), 2));
     if(dist > RADIUS)
        continue;
      dist = (dist * 2.57) / RADIUS;
      wght = exp(-dist * dist ) / sqrt(2 * PI);
      valAp += std::get<0>(old[j]) * wght;
      valEp += std::get<1>(old[j]) * wght;
      valSp += std::get<2>(old[j]) * wght;
      wsum += wght;
    }
    if(valAp / wsum > _maxAp) _maxAp = valAp / wsum;
    if(valEp / wsum > _maxEp) _maxEp = valEp / wsum;
    if(valSp / wsum > _maxSp) _maxSp = valSp / wsum;
    _tiles[i]->setPotentials(valAp / wsum, valEp / wsum, valSp / wsum);
  }
  for(auto tile : _tiles)
    tile->setPotentials(tile->getAggressionPotential() / _maxAp, tile->getEconomicPotential() / _maxEp, tile->getStrategicPotential() / _maxSp);
}