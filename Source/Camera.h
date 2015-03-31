#pragma once
#include "Position.h"

class Camera
{
public:
	Camera();
	~Camera();

	Position getPosition() const;

private:
	Position _position;
};

