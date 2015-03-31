#include "UnitWrapper.h"

UnitWrapper::UnitWrapper(BWAPI::UnitInterface *bw_unit)
// FIXME
//:_bw_unit(bw_unit),
//_position(bw_unit->getPosition())
{
	BWAPI::UnitType type = _bw_unit->getType();
	//_dps          = type.groundWeapon().damageAmount() / type.groundWeapon().damageCooldown();
	_xvelocity    = _bw_unit->getVelocityX();
	_yvelocity    = _bw_unit->getVelocityY();
}


UnitWrapper::~UnitWrapper() {}

double UnitWrapper::timeToPosition(Position to) {
	int deltax = abs(to.x - getPosition().x), deltay = abs(to.y - getPosition().y);
	return sqrt(pow(deltax / _xvelocity, 2) + pow(deltay / _yvelocity, 2));
}
