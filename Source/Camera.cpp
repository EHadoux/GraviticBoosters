#include "Camera.h"
#include "GraviticBooster.h"

#define TMIN 60
#define TMAX 150

Camera::Camera(Position position) :
_position(position) {}

Camera::~Camera() {}

void Camera::update(Map * map) {
  unsigned int time = GraviticBooster::getClock() - _lastUpdt;
  Position p = map->getMaxSumTile()->getCenterPosition();
  if((!p.compare(_position) && time > TMIN) || time > TMAX || _lastUpdt == 0) {
    _position = p;
    _lastUpdt = GraviticBooster::getClock();
  }
}
