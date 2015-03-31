#include "Tile.h"


Tile::Tile()
{
	potential = 0.0;
}


Tile::~Tile()
{
}

double Tile::getPotential() { return potential; }

void Tile::setPotential(double value) {
	potential = value;
}