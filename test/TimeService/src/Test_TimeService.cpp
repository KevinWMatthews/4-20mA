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
    alarm = TimeService_CreatePeriodicAlarm();
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
  //Can we test that things are null?
}

TEST(TimeService, DestroySupportsMultipleCalls)
{
  TimeService_Destroy();
}

TEST(TimeService, GetCallbackInfoFromNullAlarmPointer)
{
  checkPeriodicAlarm(NULL, NULL, 0);  //What value should we use?
}

TEST(TimeService, AlarmClearedAfterCreate)
{
  checkPeriodicAlarm(alarm, NULL, -1);
}

TEST(TimeService, CallbackClearedAfterDestroy)
{
  TimeService_SetPeriodicAlarm(alarm, callback, interval);
  TimeService_Destroy();

  checkPeriodicAlarm(alarm, NULL, -1);
}

TEST(TimeService, SetNullPeriodicAlarm)
{
  TimeService_SetPeriodicAlarm(NULL, callback, interval);
}

TEST(TimeService, SetPeriodicAlarm)
{
  TimeService_SetPeriodicAlarm(alarm, callback, interval);

  checkPeriodicAlarm(alarm, callback, interval);
}

TEST(TimeService, ClearNullPeriodicAlarm)
{
  TimeService_ClearPeriodicAlarm(NULL);
}

TEST(TimeService, ClearPeriodicAlarm)
{
  TimeService_SetPeriodicAlarm(alarm, callback, interval);
  TimeService_ClearPeriodicAlarm(alarm);

  checkPeriodicAlarm(alarm, NULL, -1);
}
