#include "UnitWrapper.h"

UnitWrapper::UnitWrapper(UnitInterface *bw_unit) :
_bw_unit(bw_unit),
_position(bw_unit->getPosition())
{
	UnitType type = _bw_unit->getType();
	//_dps          = type.groundWeapon().damageAmount() / type.groundWeapon().damageCooldown();
	_gas          = type.gasPrice();
	_minerals     = type.mineralPrice();
	_xvelocity    = _bw_unit->getVelocityX();
	_yvelocity    = _bw_unit->getVelocityY();
}


UnitWrapper::~UnitWrapper()
{
}

Position UnitWrapper::getPosition() const { return _position; }

double UnitWrapper::timeToPosition(Position to) {
	int deltax = abs(to.x - _position.x), deltay = abs(to.y - _position.y);
	return sqrt(pow(deltax / _xvelocity, 2) + pow(deltay / _yvelocity, 2));
}

std::vector<UnitWrapper> UnitWrapper::neighborhood() {
	std::vector<UnitWrapper> neighbors;

	return neighbors;
}

double UnitWrapper::aggresssionPotential() {
	return 0.0;
}

double UnitWrapper::economicPotential() {
	return 0.0;
}

double UnitWrapper::strategicPotential() {
	return 0.0;
}