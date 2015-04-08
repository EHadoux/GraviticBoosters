#pragma once
#include "Entity.h"

class Building : public Entity {
public:
  Building(int id, Position position, unsigned int minerals, unsigned int gas);
  ~Building();
};
