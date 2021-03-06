#pragma once

#include <vector>
#include <tuple>
#include <fstream>
#include "Position.h"
#include "Entity.h"

class Tile {
public:
  Tile(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int index);
  ~Tile();

  std::tuple<double, double, double> getPotential() const { return _potential; }
  void setPotentials(double ap, double ep, double sp);
  double maxPotential() const { return fmax(std::get<0>(_potential), fmax(std::get<1>(_potential), std::get<2>(_potential))); }
  double sumPotential() const { return (std::get<0>(_potential) +std::get<1>(_potential) +std::get<2>(_potential)) / 3.; }
  void setAllPotentials(double potential);
  double getAggressionPotential() const;
  void setAggressionPotential(double aggressionPotential);
  double getEconomicPotential() const;
  void setEconomicPotential(double economicPotential);
  double getStrategicPotential() const;
  void setStrategicPotential(double strategicPotential);
  Position getCenterPosition() const { return _centerPos; }
  std::vector<Entity*> getEntities() const;
  bool isRelevantPotentialPoint() const;
  std::vector<std::tuple<double, double, double, int>>& getPoints() const { return _points; }

private:
  Position _centerPos;
  std::tuple<double, double, double> _potential;
  mutable std::tuple<double, double, double> _referential;
  int _width, _height, _index;
  mutable std::vector<std::tuple<double, double, double, int>> _points;
  mutable std::fstream _file;
};
