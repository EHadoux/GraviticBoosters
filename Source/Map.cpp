#include "Map.h"

#define PI 3.141592653
#define RADIUS 10

Map::Map(const unsigned int width, const unsigned int height) :
_tiles(width * height) {
  _width = width;
  _height = height;
}

Map::~Map() {}

Tile* Map::getTileAt(const unsigned int x, const unsigned int y) {
  return _tiles[y * _width + x];
}

Position* Map::getPosition(const unsigned int id) {
  return new Position(_width % id, _width / id);
}


void Map::update() {

  for(auto &tile : _tiles) {
    std::vector<Entity*> * entities = tile->getEntities();
    for(auto e : *entities) {
      tile->setPotential(tile->getPotential() + e->getPotential());
    }
    tile->setPotential(tile->getPotential() / entities->size());
  }

  propagatePotential();

}

void Map::propagatePotential() {

  std::vector<Tile*> old(_tiles);
  Tile * neighbor;
  double dist;

  for(unsigned int i = 0; i < old.size(); ++i) {

    for(unsigned int x = 0; x < _width; ++x) {
      for(unsigned int y = 0; y < _height; ++y) {
        neighbor = getTileAt(x, y);
        if(neighbor != old[i]) {
          dist = getPosition(i)->euclidian(getPosition(y * _width + x));
          if(dist < RADIUS) {
            neighbor->setPotential(neighbor->getPotential() * old[i]->getPotential() * (1 + cos((dist / RADIUS)*PI) / 2));
          }
        }
      }
    }


  }
}