#pragma once

#include <vector>
#include <tuple>
#include "Position.h"
#include "Entity.h"

class Tile {
public:
  Tile(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
  ~Tile();

  std::tuple<double, double, double> getPotential() const { return _potential; }
  void setPotentials(double ap, double ep, double sp);
  double sumPotential() const { return std::get<0>(_potential) +std::get<1>(_potential) +std::get<2>(_potential); }
  void setAllPotentials(double potential);
  double getAggressionPotential() const { return std::get<0>(_potential); }
  void setAggressionPotential(double aggressionPotential);
  double getEconomicPotential() const { return std::get<1>(_potential); }
  void setEconomicPotential(double economicPotential);
  double getStrategicPotential() const { return std::get<2>(_potential); }
  void setStrategicPotential(double strategicPotential);
  Position getCenterPosition() const { return _centerPos; }
  std::vector<Entity*> getEntities() const;

private:
  Position _centerPos;
  std::tuple<double, double, double> _potential;
  int _width, _height;
};
