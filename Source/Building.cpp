#include "Building.h"

Building::Building(int id, Position position, const unsigned int minerals, const unsigned int gas) :
Entity(id, position, minerals, gas) {}

Building::~Building() {}
