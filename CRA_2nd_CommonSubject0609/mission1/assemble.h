
#define CLEAR_SCREEN "\033[H\033[2J"

enum ManufacturingQuery
{
    SelectCarType_Query,
    SelectEngine_Query,
    SelectBrakeSystem_Query,
    SelectSteeringSystem_Query,
    CheckCar_Query,
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
    ENGINE_VENDOR_WIA,
    ENGINE_WRONG
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

enum RunningTest
{
    CHECK_RUNNING = 1,
    CHECK_VALIDATION,
};

#define PROCESSING_ERROR -1

typedef struct {
    int type;
    int enginVendor;
    int brakeVendor;
    int steeringVendor;
}ManufacturedCar_t;

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void printCarType(ManufacturedCar_t& newCar);
void printSteeringVendor(ManufacturedCar_t& newCar);
void assembleNewCar(ManufacturedCar_t& newCar);
void runProducedCar(ManufacturedCar_t newCar);
void printBrakeVendor(ManufacturedCar_t& newCar);
void printEnginVendor(ManufacturedCar_t& newCar);
void testProducedCar(ManufacturedCar_t newCar);
void delay(int ms);
void printMenu(const int manufacturingStep);
int getInput(char  buf[100]);
bool isQueryStepBack(int inputQuery, int currentStep);

bool isValidCarType(const int answer);
bool isNumeric(const char* checkNumber);
bool isValidCarType(const int answer);
bool isValidEnginTypeQuery(const int inputQuery);
bool isValidBrakeSystemQuery(const int inputQuery);
bool isValidSteeringSystemQuery(const int inputQuery);
bool isValidRunningTestQuery(const int inputQuery);

int processQuery(int inputQuery, int manufacturingStep);
bool processSelectingCarType(int inputQuery);
void processCheckCar(int inputQuery);
bool processSelectingEngineVendor(int inputQuery);
bool processSelectingBrakeVendor(int inputQuery);
bool processSelectingSteeringVendor(int inputQuery);