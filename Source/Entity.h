#pragma once
#include "Position.h"
#include <vector>
#include <iostream>
#include <string>

class Entity {
public:
  Entity(Position position, unsigned int minerals, unsigned int gas);
  ~Entity();

  Position getPosition() const { return _position; }

  double aggressionPotential() const;
  double economicPotential() const;
  double strategicPotential() const;

  std::vector<Entity*> neighborhood();

  std::string toString() const;

  friend std::ostream& operator<< (std::ostream &stream, const Entity& unit);  

protected:
  Position _position;
  int _minerals, _gas;
};
