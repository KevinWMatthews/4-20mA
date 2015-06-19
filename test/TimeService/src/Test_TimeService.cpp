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

TEST(TimeService, CreateAndDestroy)
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
  POINTERS_EQUAL(NULL, TimeService_GetCallbackFunction(NULL));
  LONGS_EQUAL(PA_NULL_POINTER, TimeService_GetCallbackInterval(NULL));

  LONGS_EQUAL(PA_NULL_POINTER, TimeService_GetCounter(NULL));
  LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(NULL));
}

TEST(TimeService, AddSingleAlarm)
{
  alarm = TimeService_AddPeriodicAlarm();
  checkPeriodicAlarm(alarm, NULL, PA_INACTIVE);
  LONGS_EQUAL(0, TimeService_GetCounter(alarm));
  LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarm));
}

TEST(TimeService, AddMaxAlarms)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm();
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkPeriodicAlarm(alarmArray[i], NULL, 0);
    LONGS_EQUAL(0, TimeService_GetCounter(alarmArray[i]));
    LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarmArray[i]));
  }
}

TEST(TimeService, ExceedMaxAlarms)
{
  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    CHECK_TRUE(TimeService_AddPeriodicAlarm());
  }
  POINTERS_EQUAL(NULL, TimeService_AddPeriodicAlarm());
}

TEST(TimeService, RemoveSingleAlarm)
{
  alarm = TimeService_AddPeriodicAlarm();
  TimeService_RemovePeriodicAlarm(alarm);

  checkPeriodicAlarm(alarm, NULL, PA_UNUSED);
  LONGS_EQUAL(PA_UNUSED, TimeService_GetCounter(alarm));
  LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarm));
}

TEST(TimeService, RemoveMaxAlarms)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm();
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    TimeService_RemovePeriodicAlarm(alarmArray[i]);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkPeriodicAlarm(alarmArray[i], NULL, PA_UNUSED);
    LONGS_EQUAL(PA_UNUSED, TimeService_GetCounter(alarmArray[i]));
    LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarmArray[i]));
  }
}

TEST(TimeService, DestroySingleAlarm)
{
  alarm = TimeService_AddPeriodicAlarm();
  TimeService_Destroy();

  checkPeriodicAlarm(alarm, NULL, PA_UNUSED);
  LONGS_EQUAL(PA_UNUSED, TimeService_GetCounter(alarm));
  LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarm));
}

TEST(TimeService, DestroyMaxAlarm)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm();
  }

  TimeService_Destroy();

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkPeriodicAlarm(alarmArray[i], NULL, PA_UNUSED);
    LONGS_EQUAL(PA_UNUSED, TimeService_GetCounter(alarmArray[i]));
    LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarmArray[i]));
  }
}

TEST(TimeService, SetSinglePeriodicAlarm)
{
  alarm = TimeService_AddPeriodicAlarm();
  TimeService_SetPeriodicAlarm(alarm, callback, interval);

  checkPeriodicAlarm(alarm, callback, interval);
  LONGS_EQUAL(0, TimeService_GetCounter(alarm));
  LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarm));
}

TEST(TimeService, SetMaxAlarms)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];
  PeriodicCallback callbackArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm();
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    TimeService_SetPeriodicAlarm(alarmArray[i], callbackArray[i], i*100+interval);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkPeriodicAlarm(alarmArray[i], callbackArray[i], i*100+interval);
    LONGS_EQUAL(0, TimeService_GetCounter(alarmArray[i]));
    LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarmArray[i]));
  }
}

TEST(TimeService, PutHolesInAlarmArray)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];
  PeriodicCallback callbackArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm();
  }

  //Remove odd-numbered alarms
  for (int i = 1; i < MAX_PERIODIC_ALARMS; i += 2)
  {
    TimeService_RemovePeriodicAlarm(alarmArray[i]);
    checkPeriodicAlarm(alarmArray[i], NULL, PA_UNUSED);
    LONGS_EQUAL(PA_UNUSED, TimeService_GetCounter(alarmArray[i]));
    LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarmArray[i]));
  }

  //Check that even-numbered alarms aren't affected
  for (int i = 0; i < MAX_PERIODIC_ALARMS; i += 2)
  {
    checkPeriodicAlarm(alarmArray[i], NULL, PA_INACTIVE);
    LONGS_EQUAL(0, TimeService_GetCounter(alarmArray[i]));
    LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarmArray[i]));
  }

  //Add odd-numbered alarms again
  for (int i = 1; i < MAX_PERIODIC_ALARMS; i += 2)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm();
    checkPeriodicAlarm(alarmArray[i], NULL, PA_INACTIVE);
    LONGS_EQUAL(0, TimeService_GetCounter(alarmArray[i]));
    LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarmArray[i]));
  }

  //TimeService should be maxed out
  POINTERS_EQUAL(NULL, TimeService_AddPeriodicAlarm());
}
