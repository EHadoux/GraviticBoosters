#include "Camera.h"
#include "GraviticBooster.h"

#define TMIN 5
#define TMAX 100
#define MOVEDIST 300
#define SPEEDCAM 0.3

Camera::Camera(Position position) :
_position(position) {}

Camera::~Camera() {}

void Camera::update(Map * map) {
  unsigned int time = GraviticBooster::getClock() - _lastUpdt;
  Position p = map->getMaxSumTile()->getCenterPosition();
  double distance = p.euclidian(_position);
  if(distance > MOVEDIST) {
    if((!p.compare(_position) && time > TMIN) || time > TMAX || _lastUpdt == 0) {
      _position = p;
      _lastUpdt = GraviticBooster::getClock();
    }
  } else _position.update((1 - SPEEDCAM) * _position.getX() + SPEEDCAM * p.getX(), (1 - SPEEDCAM) * _position.getY() + SPEEDCAM * p.getY());
}
