#pragma once

#include "Unit.h"
#include <set>
#include <unordered_map>

class GraviticBooster {
private:
  static std::unordered_map<int, Entity*> _entities;
  static double _maxDistance;

public:
  static double getMaxDistance() { return GraviticBooster::_maxDistance; }
  static void setMaxDistance(double maxDistance) { GraviticBooster::_maxDistance = maxDistance; }
  static std::unordered_map<int, Entity*> getEntities() { return GraviticBooster::_entities; }
};
