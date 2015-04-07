#pragma once

#include "Unit.h"
#include <set>

class GraviticBooster {
private:
  static std::set<Unit*> _units;

public:
  static void addUnit(Unit *unit) { GraviticBooster:: _units.insert(unit); }
};

std::set<Unit*> GraviticBooster::_units;