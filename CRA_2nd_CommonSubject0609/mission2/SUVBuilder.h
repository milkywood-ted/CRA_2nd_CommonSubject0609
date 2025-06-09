#pragma once
#include "CarBuilder.h"
#include <stdio.h>

class SUVBuilder : public CarBuilder {
public:
	bool testManufacturedCar() override {
        if (newCar.getType() == CAR_TYPE_SUV && newCar.getEngineVendor() == ENGINE_VENDOR_TOYOTA)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("SUV에는 TOYOTA엔진 사용 불가\n");
            return false;
        }
        return true;
	}
    bool isValid() override {
        return !(newCar.getType() == CAR_TYPE_SUV && newCar.getEngineVendor() == ENGINE_VENDOR_TOYOTA);
    }
};