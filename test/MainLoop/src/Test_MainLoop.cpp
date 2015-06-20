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

TEST_GROUP(MainLoop)
{
  PeriodicAlarm AtodConversion;
  void setup()
  {
    // AtoD_Setup();
    TimeService_Create();
    AtodConversion = TimeService_AddPeriodicAlarm(MainLoop_AtodConversion, 1000);
    TimeService_ActivatePeriodicAlarm(AtodConversion);
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
  LONGS_EQUAL(ATOD_CONVERSION_STARTED, MainLoop_GetAtodConverstionStatus());
}
