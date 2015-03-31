#pragma once
#include <cmath>
#include "Entity.h"
#include "Position.h"
#include "BWAPI.h"

class UnitWrapper : public Entity
{
public:
	UnitWrapper(BWAPI::UnitInterface *bw_unit);
	~UnitWrapper();
	double timeToPosition(Position to);
	
private:
	BWAPI::UnitInterface *_bw_unit;
	double _xvelocity, _yvelocity;
};
