#pragma once

class AssemblingCar {
public:
	virtual bool buildCarType(int type) = 0;
	virtual bool buildEngine(int vendor) = 0;
	virtual bool buildBrake(int vendor) = 0;
	virtual bool buildSteering(int vendor) = 0;
};