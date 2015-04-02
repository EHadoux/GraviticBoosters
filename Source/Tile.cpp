#include "Tile.h"

Tile::Tile(unsigned int x, unsigned int y) {
  _potential = 0.0;
}

Tile::~Tile() {}

void Tile::setPotential(const double potential) {
  _potential = potential;
}

std::vector<Entity*>* Tile::getEntities() const {
  std::vector<Entity*> *entities;
  //TODO
  return entities;
}
