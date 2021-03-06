#pragma once

#include "Entity.h"
#include "Position.h"
#include <iostream>
#include <string>
#include <vector>

class Unit : public Entity {
public:
  Unit(unsigned int id, Position position, unsigned int minerals, unsigned int gas, double dpf,
       double velocity, unsigned int owner, bool _isWorker);
  ~Unit();

  double timeToPosition(Position to) const;
  std::vector<Unit*> unitNeighborhood() const;
  double aggressionPotential() const;
  double strategicPotential() const;
  double economicPotential() const;
  bool isCollector() const { return _isWorker; }

  std::string toString() const;

  friend std::ostream& operator<< (std::ostream &stream, const Unit& unit);

private:
  double _velocity;
  bool _isWorker;
};
