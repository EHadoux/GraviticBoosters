#pragma once
#include "HasPosition.h"
#include "HasDPSUpgrade.h"
#include "Position.h"
#include <vector>

class Entity : public HasPosition, HasDPSUpgrade {
public:
  Entity(Position position, unsigned int minerals, unsigned int gas, unsigned int dps);
  virtual ~Entity();

  double aggressionPotential() const;
  double economicPotential() const;
  double strategicPotential() const;

  std::vector<Entity*>* neighborhood() const;

protected:
  int _minerals, _gas, _dps;
};
