extern "C"
{
  #include "MainLoop.h"
  #include "TimeService.h"
  #include "AtoD.h"
  #include "LineFit.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_MainLoop.h"

#define ADC_INITIAL_VALUE 12
#define FOURTOTWENTY_INITIAL_VALUE 12

TEST_GROUP(MainLoop)
{
  PeriodicAlarm AtodConversion;
  LineFit fourToTwentyLine;
  int16_t adcReading;
  float reading;

  void setup()
  {
    TimeService_Create();
    AtodConversion = TimeService_AddPeriodicAlarm(MainLoop_AtodConversion, 1000);
    TimeService_ActivatePeriodicAlarm(AtodConversion);
    adcReading = ADC_INITIAL_VALUE;
    reading = FOURTOTWENTY_INITIAL_VALUE;

    fourToTwentyLine = LineFit_Create();
    LineFit_SetPoint1(fourToTwentyLine, 4, 4);
    LineFit_SetPoint2(fourToTwentyLine, 20, 20);
    LineFit_CalculateEquation(fourToTwentyLine);
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
  LONGS_EQUAL(ATOD_CONVERSION_STARTED, MainLoop_GetAtodConversionStatus());
}

TEST(MainLoop, ReadAtodExitsImmediatelyIfConversionWasBusy)
{
  MainLoop_Private_SetAtodConversionStatus(ATOD_CONVERSION_BUSY);

  MainLoop_GetReading(fourToTwentyLine, &reading);
  LONGS_EQUAL(ADC_INITIAL_VALUE, reading);
}

TEST(MainLoop, ReadAtodExitsIfReadBusy)
{
  MainLoop_Private_SetAtodConversionStatus(ATOD_CONVERSION_STARTED);

  mock().expectOneCall("AtoD_Read")
        .withOutputParameterReturning("adcReading", &adcReading, sizeof(int16_t))
        .andReturnValue(ATOD_READ_BUSY);
  MainLoop_GetReading(fourToTwentyLine, &reading);
  LONGS_EQUAL(ADC_INITIAL_VALUE, reading);
}

TEST(MainLoop, ReadAtodSuccess)
{
  adcReading = 14;
  MainLoop_Private_SetAtodConversionStatus(ATOD_CONVERSION_STARTED);

  mock().expectOneCall("AtoD_Read")
        .withOutputParameterReturning("adcReading", &adcReading, sizeof(int16_t))
        .andReturnValue(ATOD_READ_SUCCESS);
  MainLoop_GetReading(fourToTwentyLine, &reading);

  LONGS_EQUAL(adcReading, reading);
}
