extern "C"
{
  #include "TimeServicePrivate.h"
  #include "TimeService.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_TimeServicePrivate.h"

void callbackFunctionPrivateTest(void * argument)
{
}

TEST_GROUP(TimeServicePrivate)
{
  PeriodicAlarm alarm;
  PeriodicAlarmCallback callback;
  int16_t period;

  void setup()
  {
    TimeService_Create();
    period = 42;
    callback = &callbackFunctionPrivateTest;
    alarm = TimeService_AddPeriodicAlarm(callback, period, FALSE);
  }

  void teardown()
  {
    TimeService_Destroy();
  }
};

TEST(TimeServicePrivate, NullPointerToAnyFunctionWontCrash)
{
  POINTERS_EQUAL(NULL, TimeServicePrivate_GetCallback(NULL));
  LONGS_EQUAL(PA_NULL_POINTER, TimeServicePrivate_GetPeriod(NULL));
  TimeServicePrivate_SetCounter(NULL, 666);
  LONGS_EQUAL(PA_NULL_POINTER, TimeServicePrivate_GetCounter(NULL));
  LONGS_EQUAL(FALSE, TimeServicePrivate_GetExecuteCallbackFlag(NULL));
  TimeServicePrivate_SetExecuteCallbackFlag(NULL, FALSE);
}

TEST(TimeServicePrivate, GetCallback)
{
  POINTERS_EQUAL(&callbackFunctionPrivateTest, TimeServicePrivate_GetCallback(alarm));
}

TEST(TimeServicePrivate, GetCounter)
{
  LONGS_EQUAL(PA_INACTIVE, TimeServicePrivate_GetCounter(alarm));
}

TEST(TimeServicePrivate, SetCounter)
{
  TimeServicePrivate_SetCounter(alarm, 4242);
  LONGS_EQUAL(4242, TimeServicePrivate_GetCounter(alarm));
}

TEST(TimeServicePrivate, GetCallbackFlag)
{
  LONGS_EQUAL(FALSE, TimeServicePrivate_GetExecuteCallbackFlag(alarm));
}

TEST(TimeServicePrivate, SetCallbackFlag)
{
  TimeServicePrivate_SetExecuteCallbackFlag(alarm, TRUE);
  LONGS_EQUAL(TRUE, TimeServicePrivate_GetExecuteCallbackFlag(alarm));
}
