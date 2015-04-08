#pragma once

#include "Position.h"

class HasPosition {
public:
  HasPosition() : _position(0, 0) {}
  HasPosition(Position position) : _position(position) {}
  Position getPosition() const { return _position; }
  virtual void updatePosition(Position newposition) = 0;

protected:
  Position _position;
};