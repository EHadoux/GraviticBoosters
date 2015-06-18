#include "Tile.h"
#include "GraviticBooster.h"

Tile::Tile(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const unsigned int index) :
_centerPos(x, y) {
  _potential = std::make_tuple(.0, .0, .0);
  _referential = std::make_tuple(.0, .0, .0);
  _width = width;
  _height = height;  
  _index = index;
}

Tile::~Tile() {
  _file.open("tiles/data" + std::to_string(_index) + ".txt", std::fstream::out | std::fstream::app);
  for(auto point : _points) {    
    double agg = std::get<0>(point), eco = std::get<1>(point), strat = std::get<2>(point);
    int time = std::get<3>(point);
    _file << agg << " " << eco << " " << strat << " " << time << std::endl;
  }
  _file << std::endl << std::endl;

  _file.close();
}

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

bool Tile::isRelevantPotentialPoint() const {
  double agg = std::get<0>(_potential), eco = std::get<1>(_potential), strat = std::get<2>(_potential);
  /*bool added = false;
  if(agg - std::get<0>(_referential) >= 0.2)
    added = true;
    
  if(eco - std::get<1>(_referential) >= 0.2)
    added = true;
    
  if(strat - std::get<2>(_referential) >= 0.2)
    added = true;
    
  if(added) {*/
    /*std::get<0>(_referential) = agg;
    std::get<1>(_referential) = eco;
    std::get<2>(_referential) = strat;*/
  if((agg + eco + strat) == 0)
    return true;
    _points.push_back(std::make_tuple(agg, eco, strat, GraviticBooster::getClock()));
    std::cout << agg << " " << eco << " " << strat << std::endl;        
  //}
  //return added;
    return true;
}