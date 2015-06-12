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
  alarm = TimeService_AddPeriodicAlarm();
  checkPeriodicAlarm(alarm, NULL, 0);
}

TEST(TimeService, CallbackClearedAfterDestroy)
{
  alarm = TimeService_AddPeriodicAlarm();
  TimeService_Destroy();

  checkPeriodicAlarm(alarm, NULL, PA_UNUSED);
}

TEST(TimeService, ExceedMaxPeriodicAlarms)
{
  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    CHECK_TRUE(TimeService_AddPeriodicAlarm());
  }
  POINTERS_EQUAL(NULL, TimeService_AddPeriodicAlarm());
}

TEST(TimeService, RemovePeriodicAlarm)
{
  alarm = TimeService_AddPeriodicAlarm();
  TimeService_RemovePeriodicAlarm(alarm);
  checkPeriodicAlarm(alarm, NULL, PA_UNUSED);
}

TEST(TimeService, SetPeriodicAlarm)
{
  alarm = TimeService_AddPeriodicAlarm();
  TimeService_SetPeriodicAlarm(alarm, callback, interval);

  checkPeriodicAlarm(alarm, callback, interval);
}

TEST(TimeService, MaxAlarms_DisabledAfterCreate)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm();
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkPeriodicAlarm(alarmArray[i], NULL, 0);
  }
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
  }
}

TEST(TimeService, RemoveMaxAlarms)
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
    TimeService_RemovePeriodicAlarm(alarmArray[i]);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkPeriodicAlarm(alarmArray[i], NULL, PA_UNUSED);
  }
}

TEST(TimeService, PutHolesInArray)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];
  PeriodicCallback callbackArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm();
  }

  TimeService_RemovePeriodicAlarm(alarmArray[1]);
  TimeService_RemovePeriodicAlarm(alarmArray[3]);
  TimeService_RemovePeriodicAlarm(alarmArray[5]);
  TimeService_RemovePeriodicAlarm(alarmArray[7]);
  TimeService_RemovePeriodicAlarm(alarmArray[9]);

  alarmArray[1] = TimeService_AddPeriodicAlarm();
  alarmArray[3] = TimeService_AddPeriodicAlarm();
  alarmArray[5] = TimeService_AddPeriodicAlarm();
  alarmArray[7] = TimeService_AddPeriodicAlarm();
  alarmArray[9] = TimeService_AddPeriodicAlarm();

  POINTERS_EQUAL(NULL, TimeService_AddPeriodicAlarm());
}
