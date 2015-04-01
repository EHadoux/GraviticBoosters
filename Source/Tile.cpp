#include "Tile.h"

Tile::Tile() {
	_potential = 0.0;
}

Tile::~Tile() {}

void Tile::setPotential(const double potential) {
	_potential = potential;
	//And propagate
}
