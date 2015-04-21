#include "Tile.h"
#include "GraviticBooster.h"

Tile::Tile(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height) :
_centerPos(x, y) {
  _potential = std::make_tuple(.0, .0, .0);
  _width = width;
  _height = height;
}

Tile::~Tile() {}

void Tile::setPotentials(const double ap, const double ep, const double sp) {
  _potential = std::make_tuple(ap, ep, sp);
}

void Tile::setAllPotentials(const double potential) {
  _potential = std::make_tuple(potential, potential, potential);
}

double Tile::getAggressionPotential() const {
  double pot = std::get<0>(_potential);
  if(pot > 0)
    return pot;
  else
    return 0;
}

void Tile::setAggressionPotential(const double aggressionPotential) {
  std::get<0>(_potential) = aggressionPotential;
}

double Tile::getEconomicPotential() const {
  double pot = std::get<1>(_potential);
  if(pot > 0)
    return pot;
  else
    return 0;
}

void Tile::setEconomicPotential(const double economicPotential) {
  std::get<1>(_potential) = economicPotential;
}

double Tile::getStrategicPotential() const {
  double pot = std::get<2>(_potential);
  if(pot > 0)
    return pot;
  else
    return 0;
}

void Tile::setStrategicPotential(const double strategicPotential) {
  std::get<2>(_potential) = strategicPotential;
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
