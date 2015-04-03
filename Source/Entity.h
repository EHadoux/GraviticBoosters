#pragma once

#include "HasPosition.h"
#include "HasDPSUpgrade.h"
#include "HasTargetPosition.h"
#include "Position.h"
#include "math.h"
#include <vector>

class Entity : public HasPosition, HasDPSUpgrade {
public:
  Entity(Position position, unsigned int minerals, unsigned int gas, unsigned int dps);
  virtual ~Entity();

  virtual double aggressionPotential() = 0;
  double economicPotential() const;
  double strategicPotential() const;
  double getPotential();
  bool isEnnemy(Entity *other) const;
  std::vector<Entity*> neighborhood() const;

protected:
  int _minerals, _gas, _dps;
};
