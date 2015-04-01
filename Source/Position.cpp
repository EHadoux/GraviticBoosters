#include "Position.h"

Position::Position(const unsigned int x, const unsigned int y) {
  _x = x;
  _y = y;
}

Position::Position(const Position &orig) {
	_x = orig._x;
	_y = orig._y;
}

Position::~Position() {}
