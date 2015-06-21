extern "C"
{
  #include "MainLoop.h"
  #include "TimeService.h"
  #include "AtoD.h"
  #include "LineFit.h"
  #include "LedNumber.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_MainLoop.h"

#define ADC_INITIAL_VALUE 12
#define FOURTOTWENTY_INITIAL_VALUE 12

static int16_t ledNumberDeadDrop;

TEST_GROUP(MainLoop)
{
  PeriodicAlarm AtodConversion, displayUpdate;
  LineFit fourToTwentyLine;
  LedNumber ledDisplay;

  void setupAtodCallback(void)
  {
    AtodConversion = TimeService_AddPeriodicAlarm(MainLoop_AtodConversion, 1000);
    TimeService_ActivatePeriodicAlarm(AtodConversion);
  }

  void setupDisplayCallback(void)
  {
    displayUpdate = TimeService_AddPeriodicAlarm(MainLoop_UpdateDisplay, 250);
    TimeService_ActivatePeriodicAlarm(displayUpdate);
  }

  void setup()
  {
    MainLoop_Init(ledDisplay);
    TimeService_Create();
    setupAtodCallback();
    setupDisplayCallback();
    ledNumberDeadDrop = 0;
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

//*** Function mocks ***//
int8_t AtoD_StartConversion(void)
{
  mock().actualCall("AtoD_StartConversion");
  return mock().intReturnValue();
}

int8_t AtoD_Read(int16_t * adcReading)
{
  mock().actualCall("AtoD_Read")
        .withOutputParameter("adcReading", adcReading);
  return mock().intReturnValue();
}

float LineFit_GetOutput(LineFit self, int16_t x)
{
  mock().actualCall("LineFit_GetOutput");
  return mock().intReturnValue();
}

void LedNumber_SetNumber(LedNumber self, int16_t number)
{
  mock().actualCall("LedNumber_SetNumber")
        .withParameter("self", self)
        .withParameter("number", number);
  ledNumberDeadDrop = number;
}

void LedNumber_ShowNumber(LedNumber self)
{
  mock().actualCall("LedNumber_ShowNumber");
}


TEST(MainLoop, NoCallbacksIfIsntTime)
{
  TimeService_TimerTick();
  TimeService_ServiceAllCallbacks();
}

TEST(MainLoop, AtodConversionExecutesIfTime)
{
  TimeService_Private_SetCounter(AtodConversion, 999);
  TimeService_TimerTick();
  mock().expectOneCall("AtoD_StartConversion")
        .andReturnValue(ATOD_CONVERSION_STARTED);
  TimeService_ServiceAllCallbacks();
}

TEST(MainLoop, ReadAtodExitsImmediatelyIfConversionWasBusy)
{
  MainLoop_Private_SetAtodConversionStatus(ATOD_CONVERSION_BUSY);

  MainLoop_GetReading(ledDisplay, fourToTwentyLine);
  LONGS_EQUAL(0, ledNumberDeadDrop);
}

TEST(MainLoop, ReadAtodExitsIfReadBusy)
{
  int16_t adcOutput = 14;
  MainLoop_Private_SetAtodConversionStatus(ATOD_CONVERSION_STARTED);

  mock().expectOneCall("AtoD_Read")
        .withOutputParameterReturning("adcReading", &adcOutput, sizeof(int16_t))
        .andReturnValue(ATOD_READ_BUSY);
  MainLoop_GetReading(ledDisplay, fourToTwentyLine);
  LONGS_EQUAL(0, ledNumberDeadDrop);
}

TEST(MainLoop, ReadAtodSuccess)
{
  int16_t adcOutput = 1000;
  MainLoop_Private_SetAtodConversionStatus(ATOD_CONVERSION_STARTED);

  mock().expectOneCall("AtoD_Read")
        .withOutputParameterReturning("adcReading", &adcOutput, sizeof(int16_t))
        .andReturnValue(ATOD_READ_SUCCESS);
  mock().expectOneCall("LineFit_GetOutput")
        .andReturnValue(20);
  mock().expectOneCall("LedNumber_SetNumber")
        .withParameter("self", ledDisplay)
        .withParameter("number", 20);
  MainLoop_GetReading(ledDisplay, fourToTwentyLine);
  LONGS_EQUAL(20, ledNumberDeadDrop);
}

TEST(MainLoop, UpdateDisplayExecutesIfItsTime)
{
  TimeService_Private_SetCounter(displayUpdate, 249);
  TimeService_TimerTick();
  mock().expectOneCall("LedNumber_ShowNumber");
  TimeService_ServiceAllCallbacks();
}
