#include "Building.h"

Building::Building(Position position, const unsigned int minerals, const unsigned int gas) :
Entity(position, minerals, gas) {}

Building::~Building() {}
