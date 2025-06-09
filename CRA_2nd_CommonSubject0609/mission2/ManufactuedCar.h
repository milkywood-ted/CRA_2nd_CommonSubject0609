#pragma once
enum CarType
{
    CAR_TYPE_SEDAN = 1,
    CAR_TYPE_SUV,
    CAR_TYPE_TRUCK
};

enum Engine
{
    ENGINE_VENDOR_GM = 1,
    ENGINE_VENDOR_TOYOTA,
    ENGINE_VENDOR_WIA,
    ENGINE_WRONG
};

enum brakeSystem
{
    BRAKE_VENDOR_MANDO = 1,
    BRAKE_VENDOR_CONTINENTAL,
    BRAKE_VENDOR_BOSCH
};

enum SteeringSystem
{
    STEERING_VENDOR_BOSCH = 1,
    STEERING_VENDOR_MOBIS
};

class ManufactuedCar{
public:
	bool checkManufactured();
    void setEngine(int engineVendor);
    void setCarType(int type);
    void setBrake(int brakeVendor);
    void setSteering(int steeringVendor);
    int getType() { return type; }
    int getEngineVendor() { return engineVendor; }
    int getBrakeVendor() { return brakeVendor; }
    int getSteeringVendor() { return steeringVendor; }
private:
    int type;
    int engineVendor;
    int brakeVendor;
    int steeringVendor;
};