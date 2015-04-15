#include "Tile.h"
#include "GraviticBooster.h"

Tile::Tile(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height) :
_centerPos(x, y) {
  _aggressionPotential = 0.0;
  _strategicPotential = 0.0;
  _economicPotential = 0.0;
  _width = width;
  _height = height;
}

Tile::~Tile() {}

void Tile::setAllPotentials(const double potential) {
  _aggressionPotential = potential;
  _strategicPotential = potential;
  _economicPotential = potential;
}

void Tile::setAggressionPotential(const double aggressionPotential) {
  _aggressionPotential = aggressionPotential;
}

void Tile::setStrategicPotential(const double strategicPotential) {
  _strategicPotential = strategicPotential;
}

void Tile::setEconomicPotential(const double economicPotential) {
  _economicPotential = economicPotential;
}

std::vector<Entity*> Tile::getEntities() const {
  std::vector<Entity*> entities;
  for(auto entity : GraviticBooster::getEntities()) {
    Position p = entity.second->getPosition();
    //std::cout << "Compare (" << p.getX() << "," << p.getY() << ") (" << _centerPos.getX() << "," << _centerPos.getY() << ")" << std::endl;
    if(p.getX() <= _centerPos.getX() + _width / 2 && p.getX() > _centerPos.getX() - _width / 2 && p.getY() <= _centerPos.getY() + _height / 2 && p.getY() > _centerPos.getY() - _height / 2)
      entities.push_back(entity.second);
  }
  return entities;
}
