#include "Map.h"

Map::Map(const unsigned int w, const unsigned int h)
{
	width = w;
	height = h;

	tiles.resize(w*h);
}

Map::~Map()
{
}

Tile Map::getTileAt(int x, int y) {
	return tiles[y*width+x];
}

unsigned int Map::getWidth() const { return width; }
unsigned int Map::getHeight() const { return height; }