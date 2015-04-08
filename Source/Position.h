#pragma once

#include <cmath>

class Position {
public:
  Position(unsigned int x, unsigned int y);
  Position(const Position &orig);
  ~Position();

  void update(unsigned int x, unsigned int y);

  unsigned int getX() const { return _x; }
  unsigned int getY() const { return _y; }

  double euclidian(const Position &position) const;

  Position operator=(const Position &pos) { _x = pos._x; _y = pos._y; return pos; }

private:
  unsigned int _x, _y;
};
