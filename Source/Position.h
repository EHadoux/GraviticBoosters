#pragma once

class Position {
public:
  Position(unsigned int x, unsigned int y);
  Position(const Position &orig);
  ~Position();

  void update(unsigned int x, unsigned int y);

  unsigned int getX() const { return _x; }
  unsigned int getY() const { return _y; }

private:
  unsigned int _x, _y;
};
