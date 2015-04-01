#pragma once
#include "Position.h"

class Camera {
public:
	Camera(Position position);
	~Camera();

	Position getPosition() const { return _position; }

private:
	Position _position;
};
