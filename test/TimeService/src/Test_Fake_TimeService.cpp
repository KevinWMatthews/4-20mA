extern "C"
{
  #include "Fake_TimeService.h"
  #include "TimeService.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_Fake_TimeService.h"

TEST_GROUP(Fake_TimeService)
{
  PeriodicAlarm alarm;

  void setup()
  {
    TimeService_Create();
    Fake_TimeService_Create();
    alarm = TimeService_AddPeriodicAlarm();

    //Substitute our fake Get() function for the real one
    //Rather than manuall saving and restoring the pointer,
    //use CppUTest's built-in macro (it automatically restores the pointer!)
    UT_PTR_SET(TimeService_GetCounter,Fake_TimeService_GetCounter);
  }

  void teardown()
  {
    TimeService_Destroy();
    Fake_TimeService_Destroy();
  }
};

TEST(Fake_TimeService, FakeCounterUnusedAfterAdd)
{
  LONGS_EQUAL(PA_UNUSED, TimeService_GetCounter(alarm));
}

TEST(Fake_TimeService, SetFakeCounter)
{
  int16_t testValue = 42;
  Fake_TimeService_SetCounter(alarm, testValue);
  LONGS_EQUAL(testValue, TimeService_GetCounter(alarm));
}
