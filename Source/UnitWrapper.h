#pragma once
#include "Entity.h"
#include "BWAPI.h"
#include <vector>

using namespace BWAPI;

class UnitWrapper : public Entity
{
public:
	UnitWrapper(UnitInterface *bw_unit);
	~UnitWrapper();
	Position getPosition() const;
	double timeToPosition(Position to);
	std::vector<UnitWrapper> neighborhood();

	double aggresssionPotential();
	double economicPotential();
	double strategicPotential();

private:
	UnitInterface *_bw_unit;
	int _dps, _gas, _minerals;
	double _xvelocity, _yvelocity;
	Position _position;
};