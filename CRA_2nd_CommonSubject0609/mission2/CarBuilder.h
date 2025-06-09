#pragma once
#include "AssemblingCar.h"
#include "ManufactuedCar.h"

class CarBuilder : public AssemblingCar
{
public:
	bool buildCarType(int type) override;
	bool buildEngine(int vendor) override;
	bool buildBrake(int vendor) override;
	bool buildSteering(int vendor) override;

	virtual bool testManufacturedCar() = 0;
	virtual bool isValid() = 0;
	bool checkBoshComposition();
	bool testRunCar();
	void printCar();
	bool testManufacturing();

	ManufactuedCar ManufatureCar();
protected:
	ManufactuedCar newCar;

	bool isValidCarType(const int intputQuery);
	bool isValidEnginTypeQuery(const int inputQuery);
	bool isValidBrakeSystemQuery(const int inputQuery);
	bool isValidSteeringSystemQuery(const int inputQuery);
};

