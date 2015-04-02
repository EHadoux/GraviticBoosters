#pragma once
#include "Position.h"

class HasTargetPosition {
public:
  HasTargetPosition() : _targetPosition(0, 0) {}
  HasTargetPosition(Position position) : _targetPosition(position) {}
  Position getTargetPosition() const { return _targetPosition; }
  virtual void updateTargetPosition(Position position) = 0;

protected:
  Position _targetPosition;
};