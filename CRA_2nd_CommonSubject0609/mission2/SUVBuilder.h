#pragma once
#include "CarBuilder.h"
#include <stdio.h>

class SUVBuilder : public CarBuilder {
public:
	bool testManufacturedCar() override {
        if (newCar.getType() == CAR_TYPE_SUV && newCar.getEngineVendor() == ENGINE_VENDOR_TOYOTA)
        {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("SUV���� TOYOTA���� ��� �Ұ�\n");
            return false;
        }
        return true;
	}
    bool isValid() override {
        return !(newCar.getType() == CAR_TYPE_SUV && newCar.getEngineVendor() == ENGINE_VENDOR_TOYOTA);
    }
};