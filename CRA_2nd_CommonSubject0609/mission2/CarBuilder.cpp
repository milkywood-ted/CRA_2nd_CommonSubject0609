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
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (type == CAR_TYPE_SUV)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (type == CAR_TYPE_TRUCK)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");

    newCar.setCarType(type);

    return true;
}

bool CarBuilder::buildEngine(int vendor)
{
    if (isValidEnginTypeQuery(vendor) == false)
        return false;

    if (vendor == ENGINE_VENDOR_GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (vendor == ENGINE_VENDOR_TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (vendor == ENGINE_VENDOR_WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");

    newCar.setEngine(vendor);

    return true;
}

bool CarBuilder::buildBrake(int vendor)
{
    if (isValidBrakeSystemQuery(vendor) == false)
        return false;

    if (vendor == BRAKE_VENDOR_MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (vendor == BRAKE_VENDOR_CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (vendor == BRAKE_VENDOR_BOSCH)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");

    newCar.setBrake(vendor);

    return true;
}

bool CarBuilder::buildSteering(int vendor)
{
    if (isValidSteeringSystemQuery(vendor) == false)
        return false;

    if (vendor == STEERING_VENDOR_BOSCH)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (vendor == STEERING_VENDOR_MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");

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
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
        return false;
    }
    return true;
}

bool CarBuilder::testRunCar()
{
    if (isValid() == false) {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        return false;
    }
    if (newCar.getEngineVendor() == ENGINE_WRONG)
    {
        printf("������ ���峪�ֽ��ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        return false;
    }
    printCar();
    printf("�ڵ����� ���۵˴ϴ�.\n");

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

    printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
    delay(800);
    return false;
}

bool CarBuilder::isValidEnginTypeQuery(const int inputQuery)
{
    if (inputQuery >= ENGINE_VENDOR_GM && inputQuery <= ENGINE_WRONG)
        return true;
    
    printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
    delay(800);
    return false;
}

bool CarBuilder::isValidBrakeSystemQuery(const int inputQuery)
{
    if (inputQuery >= BRAKE_VENDOR_MANDO && inputQuery <= BRAKE_VENDOR_BOSCH)
        return true;

    printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
    delay(800);
    return false;
}

bool CarBuilder::isValidSteeringSystemQuery(const int inputQuery)
{
    if (inputQuery >= STEERING_VENDOR_BOSCH && inputQuery <= STEERING_VENDOR_MOBIS)
        return true;

    printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
    delay(800);
    return false;
}
