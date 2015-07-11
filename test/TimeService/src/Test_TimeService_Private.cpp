extern "C"
{
  #include "TimeService_Private.h"
  #include "TimeService.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_TimeService_Private.h"

void callbackFunction_PrivateTest(void * argument)
{
}

TEST_GROUP(TimeService_Private)
{
  PeriodicAlarm alarm;
  PeriodicAlarmCallback callback;
  int16_t period;

  void setup()
  {
    TimeService_Create();
    period = 42;
    callback = &callbackFunction_PrivateTest;
    alarm = TimeService_AddPeriodicAlarm(callback, period);
  }

  void teardown()
  {
    TimeService_Destroy();
  }
};

TEST(TimeService_Private, NullPointerToAnyFunctionWontCrash)
{
  POINTERS_EQUAL(NULL, TimeService_Private_GetCallback(NULL));
  LONGS_EQUAL(PA_NULL_POINTER, TimeService_Private_GetPeriod(NULL));
  TimeService_Private_SetCounter(NULL, 666);
  LONGS_EQUAL(PA_NULL_POINTER, TimeService_Private_GetCounter(NULL));
  LONGS_EQUAL(FALSE, TimeService_Private_IsCallbackTime(NULL));
}

TEST(TimeService_Private, GetCounter)
{
  LONGS_EQUAL(PA_INACTIVE, TimeService_Private_GetCounter(alarm));
}

TEST(TimeService_Private, SetCounter)
{
  TimeService_Private_SetCounter(alarm, 4242);
  LONGS_EQUAL(4242, TimeService_Private_GetCounter(alarm));
}

TEST(TimeService_Private, GetCallback)
{
  POINTERS_EQUAL(&callbackFunction_PrivateTest, TimeService_Private_GetCallback(alarm));
}

TEST(TimeService_Private, IsCallbackTime)
{
  LONGS_EQUAL(FALSE, TimeService_Private_IsCallbackTime(alarm));
  //Uhh, do we need to test when the flag is true?
  //Do we need to test this at all?
  //I kinda don't think so
}
