#include "gmock/gmock.h"

#include "AssemblingCar.h"
#include "CarBuilder.h"
#include "ManufactuedCar.h"
#include "SedanBuilder.h"
#include "SUVBuilder.h"
#include "TruckBuilder.h"

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
int new_processQuery(int inputQuery, int manufacturingStep);
CarBuilder* getBuilder(int type);
bool isValidRunningTestQuery(const int inputQuery);


TEST(Mission2TS, EXTRA_TC1)
{
    const char* test = "\0";
    bool ret = isNumeric(test);

    EXPECT_EQ(true, ret);
}
TEST(Mission2TS, EXTRA_TC1_1)
{
    const char* test = "0";
    bool ret = isNumeric(test);

    EXPECT_EQ(false, ret);
}

TEST(MIssion2TS, EXTRA_TC2)
{
    char buf[100];
    getInput(buf);
}

TEST(Misson2TS, TC1)
{
	printMenu(SelectCarType_Query);
	printMenu(SelectEngine_Query);
	printMenu(SelectBrakeSystem_Query);
	printMenu(SelectSteeringSystem_Query);
	printMenu(CheckCar_Query);
}

TEST(Mission2TS, TC2)
{
    bool ret = isQueryStepBack(0, SelectBrakeSystem_Query);

    EXPECT_EQ(true, ret);
}

TEST(MIssion2TS, TC3)
{
    int nextStep = new_processQuery(CAR_TYPE_SEDAN, SelectCarType_Query);

    EXPECT_EQ(SelectEngine_Query, nextStep);
}
TEST(MIssion2TS, TC3_1)
{
    int nextStep = new_processQuery(9, SelectCarType_Query);

    EXPECT_EQ(PROCESSING_ERROR, nextStep);
}
TEST(MIssion2TS, TC4)
{
    int nextStep = new_processQuery(CAR_TYPE_SEDAN, SelectCarType_Query);
    nextStep = new_processQuery(99, nextStep);

    EXPECT_EQ(PROCESSING_ERROR, nextStep);
}
TEST(MIssion2TS, TC4_1)
{
    int nextStep = new_processQuery(CAR_TYPE_SEDAN, SelectCarType_Query);
    nextStep = new_processQuery(ENGINE_VENDOR_GM, nextStep);

    EXPECT_EQ(SelectBrakeSystem_Query, nextStep);
}
TEST(MIssion2TS, TC5)
{
    int nextStep = new_processQuery(CAR_TYPE_SEDAN, SelectCarType_Query);
    nextStep = new_processQuery(ENGINE_VENDOR_GM, nextStep);
    nextStep = new_processQuery(BRAKE_VENDOR_CONTINENTAL, nextStep);

    EXPECT_EQ(SelectSteeringSystem_Query, nextStep);
}
TEST(MIssion2TS, TC5_1)
{
    int nextStep = new_processQuery(CAR_TYPE_SEDAN, SelectCarType_Query);
    nextStep = new_processQuery(ENGINE_VENDOR_GM, nextStep);
    nextStep = new_processQuery(99, nextStep);

    EXPECT_EQ(PROCESSING_ERROR, nextStep);
}

TEST(MIssion2TS, TC6)
{
    int nextStep = new_processQuery(CAR_TYPE_SEDAN, SelectCarType_Query);
    nextStep = new_processQuery(ENGINE_VENDOR_GM, nextStep);
    nextStep = new_processQuery(BRAKE_VENDOR_CONTINENTAL, nextStep);
    nextStep = new_processQuery(STEERING_VENDOR_BOSCH, nextStep);

    EXPECT_EQ(CheckCar_Query, nextStep);
}

TEST(MIssion2TS, TC7)
{
    CarBuilder* builder = getBuilder(CAR_TYPE_SEDAN);

    EXPECT_EQ(true, (builder != nullptr));
}
TEST(MIssion2TS, TC8)
{
    CarBuilder* builder = getBuilder(CAR_TYPE_SUV);

    EXPECT_EQ(true, (builder != nullptr));
}
TEST(MIssion2TS, TC9)
{
    CarBuilder* builder = getBuilder(CAR_TYPE_TRUCK);

    EXPECT_EQ(true, (builder != nullptr));
}

TEST(Mission2TS, TC10)
{
    int ret = isValidRunningTestQuery(0);

    EXPECT_EQ(true, ret);
}

TEST(Mission2TS, TC11)
{
    int ret = isValidRunningTestQuery(9);

    EXPECT_EQ(false, ret);
}