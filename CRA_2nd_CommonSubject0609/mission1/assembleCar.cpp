#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assemble.h"



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

#define OK_CODE 1
#define EXIT_CODE 2

#define IS_QUERY_STEPBACK (inputQuery == 0 && manufacturingStep > SelectCarType_Query)
#ifndef _DEBUG
int mission1()
{
    char userInputBuf[100];
    int manufacturingStep = SelectCarType_Query;

    while (1)
    {

        printMenu(manufacturingStep);
        if (EXIT_CODE == getInput(userInputBuf))
            break;

        // 숫자로 된 대답인지 확인
        char* checkNumber;
        int inputQuery = strtol(userInputBuf, &checkNumber, 10); // 문자열을 10진수로 변환
        if (false == isNumeric(checkNumber))
            continue;

        // 이전으로 돌아가기
        if (isQueryStepBack(inputQuery, manufacturingStep))
        {
            manufacturingStep -= 1;
            continue;
        }


        int nextStep = processQuery(inputQuery, manufacturingStep);
        if (PROCESSING_ERROR == nextStep)
            continue;

        manufacturingStep = nextStep;
    }

    return 0;
}

int processQuery(int inputQuery, int manufacturingStep)
{
    if (manufacturingStep == SelectCarType_Query)
    {
        if (false == processSelectingCarType(inputQuery))
            return PROCESSING_ERROR;
        return SelectEngine_Query;
    }
    else if (manufacturingStep == SelectEngine_Query)
    {
        if (false == processSelectingEngineVendor(inputQuery))
            return PROCESSING_ERROR;
        return SelectBrakeSystem_Query;
    }
    else if (manufacturingStep == SelectBrakeSystem_Query)
    {
        if (false == processSelectingBrakeVendor(inputQuery))
            return PROCESSING_ERROR;
        return SelectSteeringSystem_Query;
    }
    else if (manufacturingStep == SelectSteeringSystem_Query)
    {
        if (false == processSelectingSteeringVendor(inputQuery))
            return PROCESSING_ERROR;
        return CheckCar_Query;
    }
    else if (manufacturingStep == CheckCar_Query) {
        if (false == isValidRunningTestQuery(inputQuery))
            return PROCESSING_ERROR;

        if (inputQuery == 0) { // 처음으로 돌아가기
            return SelectCarType_Query;
        }
        processCheckCar(inputQuery);
    }

    return 0;
}
#endif

bool isQueryStepBack(int inputQuery, int currentStep)
{
    return (inputQuery == 0 && currentStep > SelectCarType_Query);
}

#ifndef _DEBUG
void processCheckCar(int inputQuery)
{
    ManufacturedCar_t newCar;
    assembleNewCar(newCar);
    if (inputQuery == CHECK_RUNNING) {
        runProducedCar(newCar);
        delay(2000);
    }
    else if (inputQuery == CHECK_VALIDATION) {
        printf("Test...\n");
        delay(1500);
        testProducedCar(newCar);
        delay(2000);
    }
}

bool processSelectingCarType(int inputQuery)
{
    if (false == isValidCarType(inputQuery))
        return false;
    selectCarType(inputQuery);
    delay(800);
    return true;
}
bool processSelectingEngineVendor(int inputQuery)
{
    if (false == isValidEnginTypeQuery(inputQuery))
        return false;
    selectEngine(inputQuery);
    delay(800);
    return true;
}
bool processSelectingBrakeVendor(int inputQuery)
{
    if (false == isValidBrakeSystemQuery(inputQuery))
        return false;
    selectbrakeSystem(inputQuery);
    delay(800);
    return true;
}
bool processSelectingSteeringVendor(int inputQuery)
{
    if (false == isValidSteeringSystemQuery(inputQuery))
        false;
    selectSteeringSystem(inputQuery);
    delay(800);
    return true;
}
#endif
bool isNumeric(const char *checkNumber) {
    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return false;
    }
    return true;
}


bool isValidRunningTestQuery(const int inputQuery)
{
    if (inputQuery >= 0 && inputQuery <= 2)
        return true;

    printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
    delay(800);
    return false;
}



int getInput(char  buf[100])
{
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        return EXIT_CODE;
    }
    return OK_CODE;
}

void printMenu(const int manufacturingStep)
{
    if (manufacturingStep == SelectCarType_Query)
    {
        printf(CLEAR_SCREEN);

        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (manufacturingStep == SelectEngine_Query)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
    }
    else if (manufacturingStep == SelectBrakeSystem_Query)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (manufacturingStep == SelectSteeringSystem_Query)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (manufacturingStep == CheckCar_Query)
    {
        printf(CLEAR_SCREEN);
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    printf("===============================\n");

    printf("INPUT > ");
}


#ifndef _DEBUG
bool isValidCarType(const int intputQuery)
{
    if (intputQuery >= CAR_TYPE_SEDAN && intputQuery <= CAR_TYPE_TRUCK)
        return true;

    printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
    delay(800);
    return false;
}
void selectCarType(int inputQuery)
{
    stack[SelectCarType_Query] = inputQuery;
    if (inputQuery == CAR_TYPE_SEDAN)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (inputQuery == CAR_TYPE_SUV)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (inputQuery == CAR_TYPE_TRUCK)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}


bool isValidEnginTypeQuery(const int inputQuery)
{
    if (inputQuery >= ENGINE_VENDOR_GM && inputQuery <= ENGINE_WRONG)
        return true;

    printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
    delay(800);
    return false;
}
void selectEngine(int answer)
{
    stack[SelectEngine_Query] = answer;
    if (answer == ENGINE_VENDOR_GM)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == ENGINE_VENDOR_TOYOTA)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == ENGINE_VENDOR_WIA)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

bool isValidBrakeSystemQuery(const int inputQuery)
{
    if (inputQuery >= BRAKE_VENDOR_MANDO && inputQuery <= BRAKE_VENDOR_BOSCH)
        return true;

    printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
    delay(800);
    return false;
}
void selectbrakeSystem(int inputQuery)
{
    stack[SelectBrakeSystem_Query] = inputQuery;
    if (inputQuery == BRAKE_VENDOR_MANDO)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (inputQuery == BRAKE_VENDOR_CONTINENTAL)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (inputQuery == BRAKE_VENDOR_BOSCH)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

bool isValidSteeringSystemQuery(const int inputQuery)
{
    if (inputQuery >= STEERING_VENDOR_BOSCH && inputQuery <= STEERING_VENDOR_MOBIS)
        return true;

    printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
    delay(800);
    return false;
}
void selectSteeringSystem(int answer)
{
    stack[SelectSteeringSystem_Query] = answer;
    if (answer == STEERING_VENDOR_BOSCH)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (answer == STEERING_VENDOR_MOBIS)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}


#define IS_INVALID_BOSCH_COMPOSITION (car.brakeVendor == BRAKE_VENDOR_BOSCH && car.steeringVendor != STEERING_VENDOR_BOSCH)
inline bool isValidSedan(ManufacturedCar_t &newCar)
{
    return newCar.brakeVendor != BRAKE_VENDOR_CONTINENTAL;
}
inline bool isValidSUV(ManufacturedCar_t &newCar)
{
    return !(newCar.type== CAR_TYPE_SUV && newCar.enginVendor == ENGINE_VENDOR_TOYOTA);
}
inline bool isValidTruck(ManufacturedCar_t &newCar)
{
    return newCar.enginVendor != ENGINE_VENDOR_WIA && newCar.brakeVendor != BRAKE_VENDOR_MANDO;
}
int isValidManufacturedCar(ManufacturedCar_t &car)
{
    if (car.type == CAR_TYPE_SEDAN)
        return isValidSedan(car);

    else if (car.type == CAR_TYPE_SUV)
        return isValidSUV(car);

    else if (car.type == CAR_TYPE_TRUCK)
        return isValidTruck(car);
    
    if (IS_INVALID_BOSCH_COMPOSITION)
        return false;

    return true;
}


void assembleNewCar(ManufacturedCar_t& newCar)
{
    newCar.type = stack[SelectCarType_Query];
    newCar.enginVendor = stack[SelectEngine_Query];
    newCar.brakeVendor = stack[SelectBrakeSystem_Query];
    newCar.steeringVendor = stack[SelectSteeringSystem_Query];
}

void printCarType(ManufacturedCar_t& newCar)
{
    if (newCar.type == CAR_TYPE_SEDAN)
        printf("Car Type : Sedan\n");
    if (newCar.type == CAR_TYPE_SUV)
        printf("Car Type : SUV\n");
    if (newCar.type == CAR_TYPE_TRUCK)
        printf("Car Type : Truck\n");
}
void printEnginVendor(ManufacturedCar_t& newCar)
{
    if (newCar.enginVendor == ENGINE_VENDOR_GM)
        printf("Engine : GM\n");
    if (newCar.enginVendor == ENGINE_VENDOR_TOYOTA)
        printf("Engine : TOYOTA\n");
    if (newCar.enginVendor == ENGINE_VENDOR_WIA)
        printf("Engine : WIA\n");
}
void printBrakeVendor(ManufacturedCar_t& newCar)
{
    if (newCar.brakeVendor == BRAKE_VENDOR_MANDO)
        printf("Brake System : Mando");
    if (newCar.brakeVendor == BRAKE_VENDOR_CONTINENTAL)
        printf("Brake System : Continental\n");
    if (newCar.brakeVendor == BRAKE_VENDOR_BOSCH)
        printf("Brake System : Bosch\n");
}
void printSteeringVendor(ManufacturedCar_t& newCar)
{
    if (newCar.steeringVendor == STEERING_VENDOR_BOSCH)
        printf("SteeringSystem : Bosch\n");
    if (newCar.steeringVendor == STEERING_VENDOR_MOBIS)
        printf("SteeringSystem : Mobis\n");
}
void runProducedCar(ManufacturedCar_t newCar)
{
    if (isValidManufacturedCar(newCar) == false)
    {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if (newCar.enginVendor == ENGINE_WRONG)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    printCarType(newCar);
    printEnginVendor(newCar);
    printBrakeVendor(newCar);
    printSteeringVendor(newCar);

    printf("자동차가 동작됩니다.\n");
}



void testProducedCar(ManufacturedCar_t newCar)
{
    if (newCar.type == CAR_TYPE_SEDAN && newCar.brakeVendor == BRAKE_VENDOR_CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (newCar.type == CAR_TYPE_SUV && newCar.enginVendor == ENGINE_VENDOR_TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (newCar.type == CAR_TYPE_TRUCK && newCar.enginVendor == ENGINE_VENDOR_WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (newCar.type == CAR_TYPE_TRUCK && newCar.brakeVendor == BRAKE_VENDOR_MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (newCar.brakeVendor == BRAKE_VENDOR_BOSCH && newCar.steeringVendor != STEERING_VENDOR_BOSCH)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}
#endif