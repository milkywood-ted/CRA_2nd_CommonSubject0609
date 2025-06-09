#pragma once
#include "CarBuilder.h"
#include <stdio.h>

class TruckBuilder : public CarBuilder {
public:
	bool testManufacturedCar() override {
        if(newCar.getEngineVendor() == ENGINE_VENDOR_WIA)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 WIA엔진 사용 불가\n");
            return false;
        }
        if(newCar.getBrakeVendor() == BRAKE_VENDOR_MANDO)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 Mando제동장치 사용 불가\n");
            return false;
        }
        return true;
	}

    bool isValid() override {
        return newCar.getEngineVendor() != ENGINE_VENDOR_WIA && newCar.getBrakeVendor() != BRAKE_VENDOR_MANDO;
    }
};