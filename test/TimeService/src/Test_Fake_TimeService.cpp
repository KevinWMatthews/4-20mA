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
    Fake_TimeService_SetCounter(alarm, 0);  //This should be done by Add(), but I don't want to convert that one to a function pointer too

    //Substitute our fake functions for the real ones
    //Rather than manually saving and restoring the pointer,
    //use CppUTest's built-in macro (it automatically restores the pointer!)
    UT_PTR_SET(TimeService_GetCounter, Fake_TimeService_GetCounter);
    UT_PTR_SET(TimeService_IncrementCounter, Fake_TimeService_IncrementCounter);
  }

  void teardown()
  {
    TimeService_Destroy();
    Fake_TimeService_Destroy();
  }
};

TEST(Fake_TimeService, FakeCounterUnusedAfterAdd)
{
  LONGS_EQUAL(0, TimeService_GetCounter(alarm));
}

TEST(Fake_TimeService, SetFakeCounter)
{
  int16_t testValue = 42;
  Fake_TimeService_SetCounter(alarm, testValue);
  LONGS_EQUAL(testValue, TimeService_GetCounter(alarm));
}

TEST(Fake_TimeService, IncrementFakeCounter)
{
  TimeService_IncrementCounter(alarm);
  LONGS_EQUAL(1, TimeService_GetCounter(alarm));
}
