#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum ManufacturingQuery
{
    SelectCarType_Query,
    SelectEngine_Query,
    SelectBrakeSystem_Query,
    SelectSteeringSystem_Query,
    DoRunningTest_Query,
};

enum CarType
{
    CAR_TYPE_SEDAN = 1,
    CAR_TYPE_SUV,
    CAR_TYPE_TRUCK
};

enum Engine
{
    ENGINE_VENDOR_GM = 1,
    ENGINE_VENDOR_TOYOTA,
    ENGINE_VENDOR_WIA
};

enum brakeSystem
{
    BRAKE_VENDOR_MANDO = 1,
    BRAKE_VENDOR_CONTINENTAL,
    BRAKE_VENDOR_BOSCH
};

enum SteeringSystem
{
    STEERING_VENDOR_BOSCH = 1,
    STEERING_VENDOR_MOBIS
};

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

int main()
{
    char buf[100];
    int step = SelectCarType_Query;

    while (1)
    {

        if (step == SelectCarType_Query)
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
        else if (step == SelectEngine_Query)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 엔진을 탑재할까요?\n");
            printf("0. 뒤로가기\n");
            printf("1. GM\n");
            printf("2. TOYOTA\n");
            printf("3. WIA\n");
            printf("4. 고장난 엔진\n");
        }
        else if (step == SelectBrakeSystem_Query)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 제동장치를 선택할까요?\n");
            printf("0. 뒤로가기\n");
            printf("1. MANDO\n");
            printf("2. CONTINENTAL\n");
            printf("3. BOSCH\n");
        }
        else if (step == SelectSteeringSystem_Query)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 조향장치를 선택할까요?\n");
            printf("0. 뒤로가기\n");
            printf("1. BOSCH\n");
            printf("2. MOBIS\n");
        }
        else if (step == DoRunningTest_Query)
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
        fgets(buf, sizeof(buf), stdin);

        // 엔터 개행문자 제거
        char *context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, "exit"))
        {
            printf("바이바이\n");
            break;
        }

        // 숫자로 된 대답인지 확인
        char *checkNumber;
        int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

        // 입력받은 문자가 숫자가 아니라면
        if (*checkNumber != '\0')
        {
            printf("ERROR :: 숫자만 입력 가능\n");
            delay(800);
            continue;
        }

        if (step == SelectCarType_Query && !(answer >= 1 && answer <= 3))
        {
            printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
            delay(800);
            continue;
        }

        if (step == SelectEngine_Query && !(answer >= 0 && answer <= 4))
        {
            printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
            delay(800);
            continue;
        }

        if (step == SelectBrakeSystem_Query && !(answer >= 0 && answer <= 3))
        {
            printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
            delay(800);
            continue;
        }

        if (step == SelectSteeringSystem_Query && !(answer >= 0 && answer <= 2))
        {
            printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
            delay(800);
            continue;
        }

        if (step == DoRunningTest_Query && !(answer >= 0 && answer <= 2))
        {
            printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
            delay(800);
            continue;
        }

        // 처음으로 돌아가기
        if (answer == 0 && step == DoRunningTest_Query)
        {
            step = SelectCarType_Query;
            continue;
        }

        // 이전으로 돌아가기
        if (answer == 0 && step >= 1)
        {
            step -= 1;
            continue;
        }

        if (step == SelectCarType_Query)
        {
            selectCarType(answer);
            delay(800);
            step = SelectEngine_Query;
        }
        else if (step == SelectEngine_Query)
        {
            selectEngine(answer);
            delay(800);
            step = SelectBrakeSystem_Query;
        }
        else if (step == SelectBrakeSystem_Query)
        {
            selectbrakeSystem(answer);
            delay(800);
            step = SelectSteeringSystem_Query;
        }
        else if (step == SelectSteeringSystem_Query)
        {
            selectSteeringSystem(answer);
            delay(800);
            step = DoRunningTest_Query;
        }
        else if (step == DoRunningTest_Query && answer == 1)
        {
            runProducedCar();
            delay(2000);
        }
        else if (step == DoRunningTest_Query && answer == 2)
        {
            printf("Test...\n");
            delay(1500);
            testProducedCar();
            delay(2000);
        }
    }
}

void selectCarType(int query)
{
    stack[SelectCarType_Query] = query;
    if (query == 1)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (query == 2)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (query == 3)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int query)
{
    stack[SelectEngine_Query] = query;
    if (query == 1)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (query == 2)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (query == 3)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int query)
{
    stack[SelectBrakeSystem_Query] = query;
    if (query == 1)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (query == 2)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (query == 3)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int query)
{
    stack[SelectSteeringSystem_Query] = query;
    if (query == 1)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (query == 2)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int isValidCheck()
{
    if (stack[SelectCarType_Query] == CAR_TYPE_SEDAN && stack[SelectBrakeSystem_Query] == BRAKE_VENDOR_CONTINENTAL)
    {
        return false;
    }
    else if (stack[SelectCarType_Query] == CAR_TYPE_SUV && stack[SelectEngine_Query] == ENGINE_VENDOR_TOYOTA)
    {
        return false;
    }
    else if (stack[SelectCarType_Query] == CAR_TYPE_TRUCK && stack[SelectEngine_Query] == ENGINE_VENDOR_WIA)
    {
        return false;
    }
    else if (stack[SelectCarType_Query] == CAR_TYPE_TRUCK && stack[SelectBrakeSystem_Query] == BRAKE_VENDOR_MANDO)
    {
        return false;
    }
    else if (stack[SelectBrakeSystem_Query] == BRAKE_VENDOR_BOSCH && stack[SelectSteeringSystem_Query] != STEERING_VENDOR_BOSCH)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[SelectEngine_Query] == 4)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            if (stack[SelectCarType_Query] == 1)
                printf("Car Type : Sedan\n");
            if (stack[SelectCarType_Query] == 2)
                printf("Car Type : SUV\n");
            if (stack[SelectCarType_Query] == 3)
                printf("Car Type : Truck\n");
            if (stack[SelectEngine_Query] == 1)
                printf("Engine : GM\n");
            if (stack[SelectEngine_Query] == 2)
                printf("Engine : TOYOTA\n");
            if (stack[SelectEngine_Query] == 3)
                printf("Engine : WIA\n");
            if (stack[SelectBrakeSystem_Query] == 1)
                printf("Brake System : Mando");
            if (stack[SelectBrakeSystem_Query] == 2)
                printf("Brake System : Continental\n");
            if (stack[SelectBrakeSystem_Query] == 3)
                printf("Brake System : Bosch\n");
            if (stack[SelectSteeringSystem_Query] == 1)
                printf("SteeringSystem : Bosch\n");
            if (stack[SelectSteeringSystem_Query] == 2)
                printf("SteeringSystem : Mobis\n");

            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[SelectCarType_Query] == CAR_TYPE_SEDAN && stack[SelectBrakeSystem_Query] == BRAKE_VENDOR_CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (stack[SelectCarType_Query] == CAR_TYPE_SUV && stack[SelectEngine_Query] == ENGINE_VENDOR_TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (stack[SelectCarType_Query] == CAR_TYPE_TRUCK && stack[SelectEngine_Query] == ENGINE_VENDOR_WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (stack[SelectCarType_Query] == CAR_TYPE_TRUCK && stack[SelectBrakeSystem_Query] == BRAKE_VENDOR_MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (stack[SelectBrakeSystem_Query] == BRAKE_VENDOR_BOSCH && stack[SelectSteeringSystem_Query] != STEERING_VENDOR_BOSCH)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        if (stack[SelectSteeringSystem_Query] == STEERING_VENDOR_MOBIS)
        {
            printf("Bosch엔진에는 Mobis제동장치 사용 불가\n");
        }
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}