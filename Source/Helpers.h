#include <BWAPI.h>
#include <cmath>

using namespace BWAPI;

int timeToPosition(Position from, Position to, int xvelocity, int yvelocity) {
	int deltax = abs(to.x - from.x), deltay = abs(to.y - from.y);
	return sqrt(pow(deltax / xvelocity, 2) + pow(deltay / yvelocity, 2));
}

