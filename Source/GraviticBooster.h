#pragma once

#include "Unit.h"
#include <set>

class GraviticBooster {
private:
  static std::set<Unit*> _units;
  static double _maxDistance;

public:
  static double getMaxDistance() { return GraviticBooster::_maxDistance; }
  static void setMaxDistance(double maxDistance) { GraviticBooster::_maxDistance = maxDistance; }
  static void addUnit(Unit *unit) { GraviticBooster::_units.insert(unit); }
};
