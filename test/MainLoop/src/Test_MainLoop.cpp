extern "C"
{
  #include "MainLoop.h"
  #include "TimeService.h"
  #include "AtoD.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_MainLoop.h"

#define ATOD_INITIAL_VALUE 42

TEST_GROUP(MainLoop)
{
  PeriodicAlarm AtodConversion;
  int16_t atodValue;

  void setup()
  {
    TimeService_Create();
    AtodConversion = TimeService_AddPeriodicAlarm(MainLoop_AtodConversion, 1000);
    TimeService_ActivatePeriodicAlarm(AtodConversion);
    atodValue = ATOD_INITIAL_VALUE;
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

int8_t AtoD_Read(int16_t * reading)
{
  mock().actualCall("AtoD_Read")
        .withOutputParameter("reading", reading);
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

  MainLoop_ReadAtodValue(&atodValue);
  LONGS_EQUAL(ATOD_INITIAL_VALUE, atodValue);
}

TEST(MainLoop, ReadAtodExitsIfReadBusy)
{
  MainLoop_Private_SetAtodConversionStatus(ATOD_CONVERSION_STARTED);

  mock().expectOneCall("AtoD_Read")
        .withOutputParameterReturning("reading", &atodValue, sizeof(int16_t))
        .andReturnValue(ATOD_READ_BUSY);
  MainLoop_ReadAtodValue(&atodValue);
  LONGS_EQUAL(ATOD_INITIAL_VALUE, atodValue);
}

TEST(MainLoop, ReadAtodSuccess)
{
  int16_t outputValue = ATOD_INITIAL_VALUE*2;
  MainLoop_Private_SetAtodConversionStatus(ATOD_CONVERSION_STARTED);

  mock().expectOneCall("AtoD_Read")
        .withOutputParameterReturning("reading", &outputValue, sizeof(int16_t))
        .andReturnValue(ATOD_READ_SUCCESS);
  MainLoop_ReadAtodValue(&atodValue);
  LONGS_EQUAL(ATOD_INITIAL_VALUE*2, atodValue);
}
