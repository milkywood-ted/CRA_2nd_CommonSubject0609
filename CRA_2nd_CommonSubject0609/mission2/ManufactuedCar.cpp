#include "ManufactuedCar.h"
#include <stdio.h>

bool ManufactuedCar::checkManufactured()
{
    if (type == CAR_TYPE_SEDAN && brakeVendor == BRAKE_VENDOR_CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (type == CAR_TYPE_SUV && engineVendor == ENGINE_VENDOR_TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (type == CAR_TYPE_TRUCK && engineVendor == ENGINE_VENDOR_WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (type == CAR_TYPE_TRUCK && brakeVendor == BRAKE_VENDOR_MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (brakeVendor == BRAKE_VENDOR_BOSCH && steeringVendor != STEERING_VENDOR_BOSCH)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
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
