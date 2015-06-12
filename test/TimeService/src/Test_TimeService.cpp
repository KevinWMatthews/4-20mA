extern "C"
{
  #include "TimeService.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_TimeService.h"

TEST_GROUP(TimeService)
{
  PeriodicAlarm alarm;
  PeriodicCallback callback;
  int16_t interval;

  void setup()
  {
    interval = 42;
    TimeService_Create();
    alarm = TimeService_AddPeriodicAlarm();
  }

  void teardown()
  {
    TimeService_Destroy();
  }

  void checkPeriodicAlarm(PeriodicAlarm alarm, PeriodicCallback callbackFunction, int16_t alarmPeriod)
  {
    POINTERS_EQUAL(callbackFunction, TimeService_GetCallbackFunction(alarm));
    LONGS_EQUAL(alarmPeriod, TimeService_GetCallbackInterval(alarm));
  }
};

TEST(TimeService, Create)
{
}

TEST(TimeService, DestroySupportsMultipleCalls)
{
  TimeService_Destroy();
}

TEST(TimeService, NullPointerToAnyFunctionWontCrash)
{
  TimeService_SetPeriodicAlarm(NULL, callback, interval);
  TimeService_RemovePeriodicAlarm(NULL);
  TimeService_GetCallbackFunction(NULL);
  TimeService_GetCallbackInterval(NULL);
}

TEST(TimeService, AddPeriodicAlarm)
{
  //Added in setup()
  checkPeriodicAlarm(alarm, NULL, 0);
}

TEST(TimeService, CallbackClearedAfterDestroy)
{
  TimeService_Destroy();

  checkPeriodicAlarm(alarm, NULL, PA_UNUSED);
}

TEST(TimeService, ExceedMaxPeriodicAlarms)
{
  //One alarm is created in setup(), so start the loop at 1
  for (int i = 1; i < MAX_PERIODIC_ALARMS; i++)
  {
    CHECK_TRUE(TimeService_AddPeriodicAlarm());
  }
  POINTERS_EQUAL(NULL, TimeService_AddPeriodicAlarm());
}

TEST(TimeService, RemovePeriodicAlarm)
{
  TimeService_RemovePeriodicAlarm(alarm);
  checkPeriodicAlarm(alarm, NULL, PA_UNUSED);
}

TEST(TimeService, SetPeriodicAlarm)
{
  TimeService_SetPeriodicAlarm(alarm, callback, interval);

  checkPeriodicAlarm(alarm, callback, interval);
}
