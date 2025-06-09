#pragma once
#include "CarBuilder.h"
#include <stdio.h>

class SedanBuilder : public CarBuilder {
public:
	bool testManufacturedCar() override {
        if (newCar.getType() == CAR_TYPE_SEDAN && newCar.getBrakeVendor() == BRAKE_VENDOR_CONTINENTAL)
        {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("Sedan���� Continental������ġ ��� �Ұ�\n");
            return false;
        }
        return true;
	}

    bool isValid() override {
        return newCar.getBrakeVendor() != BRAKE_VENDOR_CONTINENTAL;
    }
};