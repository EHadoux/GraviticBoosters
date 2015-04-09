#include "Map.h"

#define PI 3.141592653
#define RADIUS 10

Map::Map(const unsigned int width, const unsigned int height, const unsigned int tilew, const unsigned int tileh) :
_tiles(width * height) {
  _width = width;
  _height = height;

  for(unsigned int i = 0; i < _tiles.size(); ++i)
    _tiles[i] = new Tile((_width % i)*tilew, (_width / i)*tileh);
}

Map::~Map() {
  for(auto t : _tiles)
    delete t;
}

Tile* Map::getTileAt(const unsigned int x, const unsigned int y) const {
  return _tiles[y * _width + x];
}

Position* Map::getPosition(const unsigned int id) const {
  return new Position(_width % id, _width / id);
}


void Map::update() {
  for(auto tile : _tiles) {
    auto entities = tile->getEntities();
    for(auto e : entities)
      tile->setPotential(tile->getPotential() + e->getPotential());
    tile->setPotential(tile->getPotential() / entities.size());
    std::cout << "update tile" << std::endl;
  }
  propagatePotential();
}

void Map::propagatePotential() {
  std::vector<Tile*> old(_tiles);
  Tile *neighbor;
  double dist;

  for(unsigned int i = 0; i < old.size(); ++i)
    for(unsigned int x = 0; x < _width; ++x)
      for(unsigned int y = 0; y < _height; ++y) {
        neighbor = getTileAt(x, y);
        if(neighbor != old[i]) {
          dist = getPosition(i)->euclidian(*getPosition(y * _width + x));
          if(dist < RADIUS)
            neighbor->setPotential((neighbor->getPotential() + old[i]->getPotential() * (1 + cos((dist / RADIUS)*PI) / 2)) / 2);
        }
      }
}