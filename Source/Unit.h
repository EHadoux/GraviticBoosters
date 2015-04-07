#pragma once
#include "Entity.h"
#include "Position.h"
#include <iostream>
#include <string>

class Unit : public Entity {
public:
  Unit(Position position, unsigned int minerals, unsigned int gas, double dpf, double velocity);
  ~Unit();
  double timeToPosition(Position to);

  std::string toString() const;

  friend std::ostream& operator<< (std::ostream &stream, const Unit& unit);

private:
  double _velocity, _dpf;
};
