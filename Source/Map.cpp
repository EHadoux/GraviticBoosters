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

void Map::update() {

  for(unsigned int i = 0; i < _tiles.size(); ++i) {

    std::vector<Entity> entities = getEntities(_tiles[i]);

    for(unsigned int j = 0; j < entities.size(); ++j)
      _tiles[i].potential += (Entity*)entities[j].getPotential();

    _tiles[i].potential /= entities.size();

  }

  propagatePotential();

}

void Map::propagatePotential() {

  std::vector<Tile*> old(_tiles);
  Tile neighbor;
  Position position;
  int dist;

  for(unsigned int i = 0; i < old.size(); ++i) {

    for(unsigned int w = 0; w < _width; ++w) {
      for(unsigned int h = 0; h < _height; ++h) {

        position.x = w;
        position.y = h;
        neighbor = getTile(position);

        if(neigbor != tile) {
          dist = old[i].distanceTo(w, h);
          if(dist < RADIUS) {
            neighbor.potential = old[w*_width + h] * old[i].getPotential() * (1 + cos((dist / RADIUS)*PI) / 2);
          }
        }
      }
    }


  }
