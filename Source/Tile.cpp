#include "Tile.h"
#include "GraviticBooster.h"

Tile::Tile(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height) :
_centerPos(x, y) {
  _potential = 0.0;
  _width = width;
  _height = height;
}

Tile::~Tile() {}

void Tile::setPotential(const double potential) {
  _potential = potential;
}

std::vector<Entity*> Tile::getEntities() const {
  std::vector<Entity*> entities;
  for(auto entity : GraviticBooster::getEntities()) {
    Position p = entity.second->getPosition();
    if(p.getX() <= _centerPos.getX() + _width / 2 && p.getX() > _centerPos.getX() - _width / 2 && p.getY() <= _centerPos.getY() + _height / 2 && p.getY() > _centerPos.getY() - _height / 2)
      entities.push_back(entity.second);
  }
  return entities;
}
