#pragma once

#include "Position.h"
#include "Map.h"

#include <cmath>

class Camera {
public:
  Camera(Position position);
  ~Camera();

  Position getPosition() const { return _position; }
  void setPosition(const Position &position) { _position = position; }
  void update(Map * map);

private:
  Position _position;
  unsigned int _lastUpdt;
};
