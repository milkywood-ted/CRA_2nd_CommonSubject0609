#pragma once
#include "CarBuilder.h"
#include <stdio.h>

class TruckBuilder : public CarBuilder {
public:
	bool testManufacturedCar() override {
        if(newCar.getEngineVendor() == ENGINE_VENDOR_WIA)
        {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("Truck���� WIA���� ��� �Ұ�\n");
            return false;
        }
        if(newCar.getBrakeVendor() == BRAKE_VENDOR_MANDO)
        {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("Truck���� Mando������ġ ��� �Ұ�\n");
            return false;
        }
        return true;
	}

    bool isValid() override {
        return newCar.getEngineVendor() != ENGINE_VENDOR_WIA && newCar.getBrakeVendor() != BRAKE_VENDOR_MANDO;
    }
};