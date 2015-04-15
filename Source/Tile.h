#pragma once

#include <vector>
#include "Position.h"
#include "Entity.h"

class Tile {
public:
  Tile(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
  ~Tile();

  double getPotential() const { return _aggressionPotential + _economicPotential + _strategicPotential; }
  void setAllPotentials(double potential);
  double getAggressionPotential() const { return _aggressionPotential; }
  void setAggressionPotential(double aggressionPotential);
  double getEconomicPotential() const { return _economicPotential; }
  void setEconomicPotential(double economicPotential);
  double getStrategicPotential() const { return _strategicPotential; }
  void setStrategicPotential(double strategicPotential);
  Position getCenterPosition() const { return _centerPos; }
  std::vector<Entity*> getEntities() const;

private:
  Position _centerPos;
  double _aggressionPotential, _economicPotential, _strategicPotential;
  int _width, _height;
};
