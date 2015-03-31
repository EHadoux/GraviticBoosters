#include "Map.h"

Map::Map(const unsigned int width, const unsigned int height) :
_tiles(w*h) {
	_width  = width;
	_height = height;
}

Map::~Map() {}

Tile* Map::getTileAt(unsigned int x, unsigned int y) {
	return tiles[y*width+x];
}
