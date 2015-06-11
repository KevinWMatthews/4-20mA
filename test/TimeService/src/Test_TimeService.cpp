extern "C"
{
  #include "TimeService.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_TimeService.h"

TEST_GROUP(TimeService)
{
  PeriodicCallback callback;
  int16_t interval;

  void setup()
  {
    interval = 42;
    TimeService_Create();
  }

  void teardown()
  {
    TimeService_Destroy();
  }

  void checkPeriodicAlarm(PeriodicCallback callbackFunction, int16_t alarmPeriod)
  {
    POINTERS_EQUAL(callbackFunction, TimeService_GetCallbackFunction());
    LONGS_EQUAL(alarmPeriod, TimeService_GetCallbackInterval());
  }
};

TEST(TimeService, Create)
{
  checkPeriodicAlarm(NULL, -1);
}

TEST(TimeService, DestroySupportsMultipleCalls)
{
  TimeService_Destroy();
}

TEST(TimeService, CallbackClearedAfterDestroy)
{
  TimeService_SetPeriodicAlarm(callback, interval);
  TimeService_Destroy();

  checkPeriodicAlarm(NULL, -1);
}

TEST(TimeService, SetCallbackFunction)
{
  PeriodicCallback callback;

  TimeService_SetPeriodicAlarm(callback, interval);

  checkPeriodicAlarm(callback, interval);
}
