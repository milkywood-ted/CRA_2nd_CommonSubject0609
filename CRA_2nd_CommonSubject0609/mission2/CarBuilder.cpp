#include "CarBuilder.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}
*/
void delay(int ms);

bool CarBuilder::buildCarType(int type)
{
    if (isValidCarType(type) == false)
        return false;

    if (type == CAR_TYPE_SEDAN)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (type == CAR_TYPE_SUV)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (type == CAR_TYPE_TRUCK)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");

    newCar.setCarType(type);

    return true;
}

bool CarBuilder::buildEngine(int vendor)
{
    if (isValidEnginTypeQuery(vendor) == false)
        return false;

    if (vendor == ENGINE_VENDOR_GM)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (vendor == ENGINE_VENDOR_TOYOTA)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (vendor == ENGINE_VENDOR_WIA)
        printf("WIA 엔진을 선택하셨습니다.\n");

    newCar.setEngine(vendor);

    return true;
}

bool CarBuilder::buildBrake(int vendor)
{
    if (isValidBrakeSystemQuery(vendor) == false)
        return false;

    if (vendor == BRAKE_VENDOR_MANDO)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (vendor == BRAKE_VENDOR_CONTINENTAL)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (vendor == BRAKE_VENDOR_BOSCH)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");

    newCar.setBrake(vendor);

    return true;
}

bool CarBuilder::buildSteering(int vendor)
{
    if (isValidSteeringSystemQuery(vendor) == false)
        return false;

    if (vendor == STEERING_VENDOR_BOSCH)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (vendor == STEERING_VENDOR_MOBIS)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");

    newCar.setSteering(vendor);

    return true;
}

bool CarBuilder::testManufacturedCar()
{
    return false;
}

bool CarBuilder::checkBoshComposition()
{
    if (newCar.getBrakeVendor() == BRAKE_VENDOR_BOSCH && newCar.getSteeringVendor() != STEERING_VENDOR_BOSCH)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
        return false;
    }
    return true;
}

bool CarBuilder::testRunCar()
{
    if (isValid() == false) {
        printf("자동차가 동작되지 않습니다\n");
        return false;
    }
    if (newCar.getEngineVendor() == ENGINE_WRONG)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return false;
    }
    printCar();
    printf("자동차가 동작됩니다.\n");

    return true;
}

void CarBuilder::printCar()
{
    if (newCar.getType() == CAR_TYPE_SEDAN)
        printf("Car Type : Sedan\n");
    if (newCar.getType() == CAR_TYPE_SUV)
        printf("Car Type : SUV\n");
    if (newCar.getType() == CAR_TYPE_TRUCK)
        printf("Car Type : Truck\n");

    if (newCar.getEngineVendor() == ENGINE_VENDOR_GM)
        printf("Engine : GM\n");
    if (newCar.getEngineVendor() == ENGINE_VENDOR_TOYOTA)
        printf("Engine : TOYOTA\n");
    if (newCar.getEngineVendor() == ENGINE_VENDOR_WIA)
        printf("Engine : WIA\n");

    if (newCar.getBrakeVendor() == BRAKE_VENDOR_MANDO)
        printf("Brake System : Mando");
    if (newCar.getBrakeVendor() == BRAKE_VENDOR_CONTINENTAL)
        printf("Brake System : Continental\n");
    if (newCar.getBrakeVendor() == BRAKE_VENDOR_BOSCH)
        printf("Brake System : Bosch\n");

    if (newCar.getSteeringVendor() == STEERING_VENDOR_BOSCH)
        printf("SteeringSystem : Bosch\n");
    if (newCar.getSteeringVendor() == STEERING_VENDOR_MOBIS)
        printf("SteeringSystem : Mobis\n");
}

bool CarBuilder::testManufacturing()
{
    if (checkBoshComposition() == false) {
        return false;
    }
    if (testManufacturedCar() == false) {
        return false;
    }
    return false;
}

ManufactuedCar CarBuilder::ManufatureCar()
{
    return newCar;
}

bool CarBuilder::isValidCarType(const int intputQuery)
{
    if (intputQuery >= CAR_TYPE_SEDAN && intputQuery <= CAR_TYPE_TRUCK)
        return true;

    printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
    delay(800);
    return false;
}

bool CarBuilder::isValidEnginTypeQuery(const int inputQuery)
{
    if (inputQuery >= ENGINE_VENDOR_GM && inputQuery <= ENGINE_WRONG)
        return true;
    
    printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
    delay(800);
    return false;
}

bool CarBuilder::isValidBrakeSystemQuery(const int inputQuery)
{
    if (inputQuery >= BRAKE_VENDOR_MANDO && inputQuery <= BRAKE_VENDOR_BOSCH)
        return true;

    printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
    delay(800);
    return false;
}

bool CarBuilder::isValidSteeringSystemQuery(const int inputQuery)
{
    if (inputQuery >= STEERING_VENDOR_BOSCH && inputQuery <= STEERING_VENDOR_MOBIS)
        return true;

    printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
    delay(800);
    return false;
}
