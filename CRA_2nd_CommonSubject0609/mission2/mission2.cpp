#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "AssemblingCar.h"
#include "CarBuilder.h"
#include "ManufactuedCar.h"
#include "SedanBuilder.h"
#include "SUVBuilder.h"
#include "TruckBuilder.h"

#define CLEAR_SCREEN "\033[H\033[2J"
enum ManufacturingQuery
{
    SelectCarType_Query,
    SelectEngine_Query,
    SelectBrakeSystem_Query,
    SelectSteeringSystem_Query,
    CheckCar_Query,
};

enum RunningTest
{
    CHECK_RUNNING = 1,
    CHECK_VALIDATION,
};

#define OK_CODE 1
#define EXIT_CODE 2
#define PROCESSING_ERROR -1
void delay(int ms);
int getInput(char  buf[100]);

void printMenu(const int manufacturingStep);

bool isNumeric(const char* checkNumber);

bool isQueryStepBack(int inputQuery, int currentStep);


CarBuilder *getBuilder(int type)
{
    if (type == CAR_TYPE_SEDAN)
        return new SedanBuilder();
    if (type == CAR_TYPE_SUV)
        return new SUVBuilder();
    if (type == CAR_TYPE_TRUCK)
        return new TruckBuilder();

    return nullptr;
}

bool isValidRunningTestQuery(const int inputQuery);

static CarBuilder* builder = NULL;
int new_processQuery(int inputQuery, int manufacturingStep)
{

    if (manufacturingStep == SelectCarType_Query)
    {
        builder = getBuilder(inputQuery);
        if (builder == nullptr)
            return PROCESSING_ERROR;
        if(false == builder->buildCarType(inputQuery))
            return PROCESSING_ERROR;
        return SelectEngine_Query;
    }
    else if (manufacturingStep == SelectEngine_Query)
    {
        if (false == builder->buildEngine(inputQuery))
            return PROCESSING_ERROR;
        return SelectBrakeSystem_Query;
    }
    else if (manufacturingStep == SelectBrakeSystem_Query)
    {
        if (false == builder->buildBrake(inputQuery))
            return PROCESSING_ERROR;
        return SelectSteeringSystem_Query;
    }
    else if (manufacturingStep == SelectSteeringSystem_Query)
    {
        if (false == builder->buildSteering(inputQuery))
            return PROCESSING_ERROR;
        return CheckCar_Query;
    }
    else if (manufacturingStep == CheckCar_Query) {

        if (false == isValidRunningTestQuery(inputQuery))
            return PROCESSING_ERROR;

        if (inputQuery == 0) { // ó������ ���ư���
            return SelectCarType_Query;
        }

        if (inputQuery == CHECK_RUNNING) {
            builder->testRunCar();
            delay(2000);
        }
        else if (inputQuery == CHECK_VALIDATION) {
            printf("Test...\n");
            delay(1500);
            builder->testManufacturing();
            delay(2000);
        }
        
    }

    return 0;
    
}

int mission2()
{
    char userInputBuf[100];
    int manufacturingStep = SelectCarType_Query;

    while (1)
    {

        printMenu(manufacturingStep);
        if (EXIT_CODE == getInput(userInputBuf))
            break;

        // ���ڷ� �� ������� Ȯ��
        char* checkNumber;
        int inputQuery = strtol(userInputBuf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ
        if (false == isNumeric(checkNumber))
            continue;

        // �������� ���ư���
        if (isQueryStepBack(inputQuery, manufacturingStep))
        {
            manufacturingStep -= 1;
            continue;
        }


        int nextStep = new_processQuery(inputQuery, manufacturingStep);
        if (PROCESSING_ERROR == nextStep)
            continue;

        manufacturingStep = nextStep;
    }

    return 0;
}