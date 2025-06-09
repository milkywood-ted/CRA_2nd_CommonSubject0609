#pragma once
#include "CarBuilder.h"
#include <stdio.h>

class SedanBuilder : public CarBuilder {
public:
	bool testManufacturedCar() override {
        if (newCar.getType() == CAR_TYPE_SEDAN && newCar.getBrakeVendor() == BRAKE_VENDOR_CONTINENTAL)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Sedan에는 Continental제동장치 사용 불가\n");
            return false;
        }
        return true;
	}

    bool isValid() override {
        return newCar.getBrakeVendor() != BRAKE_VENDOR_CONTINENTAL;
    }
};