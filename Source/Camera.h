#pragma once
#include "Position.h"

class Camera {
public:
	Camera();
	~Camera();

	Position getPosition() const { return _position; }

private:
	Position _position;
};
