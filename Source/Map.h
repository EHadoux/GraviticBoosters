#pragma once
#include "Tile.h"
#include <vector>

class Map
{
public:
	Map(const unsigned int w, const unsigned int h);
	~Map();

	unsigned int getWidth() const;
	unsigned int getHeight() const;

	Tile getTileAt(int x, int y);

private:
	int width, height;
	std::vector<Tile> tiles;

};

