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

        if (inputQuery == 0) { // ó������ ���ư���
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
    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*checkNumber != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(800);
        return false;
    }
    return true;
}


bool isValidRunningTestQuery(const int inputQuery)
{
    if (inputQuery >= 0 && inputQuery <= 2)
        return true;

    printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
    delay(800);
    return false;
}



int getInput(char  buf[100])
{
    fgets(buf, sizeof(buf), stdin);

    // ���� ���๮�� ����
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("���̹���\n");
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
        printf("� ���� Ÿ���� �����ұ��?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (manufacturingStep == SelectEngine_Query)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. ���峭 ����\n");
    }
    else if (manufacturingStep == SelectBrakeSystem_Query)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (manufacturingStep == SelectSteeringSystem_Query)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (manufacturingStep == CheckCar_Query)
    {
        printf(CLEAR_SCREEN);
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("0. ó�� ȭ������ ���ư���\n");
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

    printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
    delay(800);
    return false;
}
void selectCarType(int inputQuery)
{
    stack[SelectCarType_Query] = inputQuery;
    if (inputQuery == CAR_TYPE_SEDAN)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (inputQuery == CAR_TYPE_SUV)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (inputQuery == CAR_TYPE_TRUCK)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}


bool isValidEnginTypeQuery(const int inputQuery)
{
    if (inputQuery >= ENGINE_VENDOR_GM && inputQuery <= ENGINE_WRONG)
        return true;

    printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
    delay(800);
    return false;
}
void selectEngine(int answer)
{
    stack[SelectEngine_Query] = answer;
    if (answer == ENGINE_VENDOR_GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == ENGINE_VENDOR_TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == ENGINE_VENDOR_WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

bool isValidBrakeSystemQuery(const int inputQuery)
{
    if (inputQuery >= BRAKE_VENDOR_MANDO && inputQuery <= BRAKE_VENDOR_BOSCH)
        return true;

    printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
    delay(800);
    return false;
}
void selectbrakeSystem(int inputQuery)
{
    stack[SelectBrakeSystem_Query] = inputQuery;
    if (inputQuery == BRAKE_VENDOR_MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (inputQuery == BRAKE_VENDOR_CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (inputQuery == BRAKE_VENDOR_BOSCH)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

bool isValidSteeringSystemQuery(const int inputQuery)
{
    if (inputQuery >= STEERING_VENDOR_BOSCH && inputQuery <= STEERING_VENDOR_MOBIS)
        return true;

    printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
    delay(800);
    return false;
}
void selectSteeringSystem(int answer)
{
    stack[SelectSteeringSystem_Query] = answer;
    if (answer == STEERING_VENDOR_BOSCH)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == STEERING_VENDOR_MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
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
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        return;
    }

    if (newCar.enginVendor == ENGINE_WRONG)
    {
        printf("������ ���峪�ֽ��ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        return;
    }

    printCarType(newCar);
    printEnginVendor(newCar);
    printBrakeVendor(newCar);
    printSteeringVendor(newCar);

    printf("�ڵ����� ���۵˴ϴ�.\n");
}



void testProducedCar(ManufacturedCar_t newCar)
{
    if (newCar.type == CAR_TYPE_SEDAN && newCar.brakeVendor == BRAKE_VENDOR_CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (newCar.type == CAR_TYPE_SUV && newCar.enginVendor == ENGINE_VENDOR_TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (newCar.type == CAR_TYPE_TRUCK && newCar.enginVendor == ENGINE_VENDOR_WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (newCar.type == CAR_TYPE_TRUCK && newCar.brakeVendor == BRAKE_VENDOR_MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (newCar.brakeVendor == BRAKE_VENDOR_BOSCH && newCar.steeringVendor != STEERING_VENDOR_BOSCH)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}
#endif