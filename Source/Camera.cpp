#include "Camera.h"

Camera::Camera(Position position) :
_position(position) {}

Camera::~Camera() {}

void Camera::update(Map * map) {
  _position = map->getMaxTile()->getCenterPosition();
}
