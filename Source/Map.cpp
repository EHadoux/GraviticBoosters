#include "Map.h"

Map::Map(const unsigned int width, const unsigned int height) :
_tiles(width * height) {
	_width  = width;
	_height = height;
}

Map::~Map() {}

Tile* Map::getTileAt(const unsigned int x, const unsigned int y) {
	return _tiles[y * _width + x];
}
