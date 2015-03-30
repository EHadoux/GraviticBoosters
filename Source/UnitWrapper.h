#pragma once
#include "Entity.h"
#include "BWAPI.h"

using namespace BWAPI;

class UnitWrapper : public Entity
{
public:
	UnitWrapper(UnitInterface *bw_unit);
	~UnitWrapper();
	Position getPosition() const;
	double timeToPosition(Position to);

private:
	UnitInterface *_bw_unit;
	int _dps, _gas, _minerals;
	double _xvelocity, _yvelocity;
	Position _position;
};

