#include "Position.h"

Position::Position(const unsigned int x, const unsigned int y) {
  _x = x;
  _y = y;
}

Position::Position(const Position &orig) {
  _x = orig._x;
  _y = orig._y;
}

void Position::update(const unsigned int x, const unsigned int y) {
  _x = x;
  _y = y;
}

Position::~Position() {}

double Position::euclidian(const Position &position) {
  return sqrt(pow((double)position._x - _x, 2) + pow((double)position._y - _y, 2));
}
