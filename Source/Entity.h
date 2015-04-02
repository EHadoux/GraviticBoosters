#pragma once
#include "Position.h"
#include <vector>

class Entity {
public:
  Entity(Position position, unsigned int minerals, unsigned int gas);
  ~Entity();

  Position getPosition() const { return _position; }

  double aggressionPotential() const;
  double economicPotential() const;
  double strategicPotential() const;

  std::vector<Entity*> neighborhood();

protected:
  Position _position;
  int _minerals, _gas;
};
