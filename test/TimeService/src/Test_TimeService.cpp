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
  PeriodicAlarm alarm;
  alarm = TimeService_CreatePeriodicAlarm();

  checkPeriodicAlarm(alarm, NULL, -1);
}


// TEST(TimeService, CallbackClearedAfterDestroy)
// {
//   TimeService_SetPeriodicAlarm(callback, interval);
//   TimeService_Destroy();

//   checkPeriodicAlarm(NULL, -1);
// }

// TEST(TimeService, SetPeriodicAlarm)
// {
//   TimeService_SetPeriodicAlarm(callback, interval);

//   checkPeriodicAlarm(callback, interval);
// }

// TEST(TimeService, CancelPeriodicAlarm)
// {
//   TimeService_SetPeriodicAlarm(callback, interval);
//   TimeService_ClearPeriodicAlarm(callback, interval);

//   checkPeriodicAlarm(NULL, -1);
// }
