#include "ManufactuedCar.h"
#include <stdio.h>

bool ManufactuedCar::checkManufactured()
{
    if (type == CAR_TYPE_SEDAN && brakeVendor == BRAKE_VENDOR_CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (type == CAR_TYPE_SUV && engineVendor == ENGINE_VENDOR_TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (type == CAR_TYPE_TRUCK && engineVendor == ENGINE_VENDOR_WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (type == CAR_TYPE_TRUCK && brakeVendor == BRAKE_VENDOR_MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (brakeVendor == BRAKE_VENDOR_BOSCH && steeringVendor != STEERING_VENDOR_BOSCH)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
        return true;
    }
    return false;
}

void ManufactuedCar::setEngine(int _engineVendor)
{
    engineVendor = _engineVendor;
}

void ManufactuedCar::setCarType(int _type)
{
    type = _type;
}

void ManufactuedCar::setBrake(int _brakeVendor)
{
    brakeVendor = _brakeVendor;
}

void ManufactuedCar::setSteering(int _steeringVendor)
{
    steeringVendor = _steeringVendor;
}
