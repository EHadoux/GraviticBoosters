#pragma once
#include "HasPosition.h"
#include "Position.h"
#include <vector>

class Entity : public HasPosition {
public:
  Entity(Position position, unsigned int minerals, unsigned int gas);
  ~Entity();

	double aggressionPotential() const;
	double economicPotential() const;
	double strategicPotential() const;

  std::vector<Entity*> neighborhood();

protected:
	int _minerals, _gas;
};
