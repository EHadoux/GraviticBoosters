#pragma once

#include <cmath>

class Position {
public:
  Position(int x, int y);
  Position(const Position &orig);
  ~Position();

  void update(int x, int y);

  unsigned int getX() const { return _x; }
  unsigned int getY() const { return _y; }

  double euclidian(const Position &position) const;
  bool compare(const Position &pos) { return _x == pos._x && _y == pos._y; }
  Position operator=(const Position &pos) { _x = pos._x; _y = pos._y; return pos; }

private:
  int _x, _y;
};
