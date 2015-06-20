extern "C"
{
  #include "TimeService.h"
  #include <stdio.h>
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_TimeService.h"

void callbackFunction(void)
{
  mock().actualCall("callbackFunction");
}

void callbackFunction2(void)
{
  mock().actualCall("callbackFunction2");
}

void callbackFunction3(void)
{
  mock().actualCall("callbackFunction3");
}

TEST_GROUP(TimeService)
{
  PeriodicAlarm alarm;
  PeriodicAlarmCallback callback;
  int16_t period;

  void setup()
  {
    period = 42;
    TimeService_Create();
  }

  void teardown()
  {
    TimeService_Destroy();
    mock().checkExpectations();
    mock().clear();
  }

  void checkCallbackAndPeriod(PeriodicAlarm alarm, PeriodicAlarmCallback callbackFunction, int16_t alarmPeriod)
  {
    POINTERS_EQUAL(callbackFunction, TimeService_Private_GetCallback(alarm));
    LONGS_EQUAL(alarmPeriod, TimeService_Private_GetPeriod(alarm));
  }

  void checkCounterAndFlag(PeriodicAlarm self, int16_t counter, BOOL executeNow)
  {
    LONGS_EQUAL(counter, TimeService_Private_GetCounter(self));
    LONGS_EQUAL(executeNow, TimeService_Private_IsCallbackTime(self));
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
  TimeService_RemovePeriodicAlarm(NULL);

  POINTERS_EQUAL(NULL, TimeService_Private_GetCallback(NULL));
  LONGS_EQUAL(PA_NULL_POINTER, TimeService_Private_GetPeriod(NULL));
  TimeService_Private_SetCounter(NULL, 666);
  LONGS_EQUAL(PA_NULL_POINTER, TimeService_Private_GetCounter(NULL));
  TimeService_Private_IncrementCounter(NULL);
  LONGS_EQUAL(FALSE, TimeService_Private_IsCallbackTime(NULL));
}

TEST(TimeService, AddSingleAlarm)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  checkCallbackAndPeriod(alarm, callback, period);
  checkCounterAndFlag(alarm, PA_INACTIVE, FALSE);
}

TEST(TimeService, AddMaxAlarms)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm(callback, period);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkCallbackAndPeriod(alarmArray[i], callback, period);
    checkCounterAndFlag(alarmArray[i], PA_INACTIVE, FALSE);
  }
}

TEST(TimeService, ExceedMaxAlarms)
{
  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    CHECK_TRUE(TimeService_AddPeriodicAlarm(callback, period));
  }
  POINTERS_EQUAL(NULL, TimeService_AddPeriodicAlarm(callback, period));
}

TEST(TimeService, RemoveSingleAlarm)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_RemovePeriodicAlarm(alarm);

  checkCallbackAndPeriod(alarm, NULL, PA_UNUSED);
  checkCounterAndFlag(alarm, PA_UNUSED, FALSE);
}

TEST(TimeService, RemoveMaxAlarms)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm(callback, period);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    TimeService_RemovePeriodicAlarm(alarmArray[i]);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkCallbackAndPeriod(alarmArray[i], NULL, PA_UNUSED);
    checkCounterAndFlag(alarmArray[i], PA_UNUSED, FALSE);
  }
}

TEST(TimeService, DestroySingleAlarm)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_Destroy();

  checkCallbackAndPeriod(alarm, NULL, PA_UNUSED);
  checkCounterAndFlag(alarm, PA_UNUSED, FALSE);
}

TEST(TimeService, DestroyMaxAlarm)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm(callback, period);
  }

  TimeService_Destroy();

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkCallbackAndPeriod(alarmArray[i], NULL, PA_UNUSED);
    checkCounterAndFlag(alarmArray[i], PA_UNUSED, FALSE);
  }
}

TEST(TimeService, SetSinglePeriodicAlarm)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  //TODO activate
  TimeService_Private_SetCounter(alarm, 0);
  checkCallbackAndPeriod(alarm, callback, period);
  LONGS_EQUAL(PA_COUNTER_RESET_VALUE, TimeService_Private_GetCounter(alarm));
  LONGS_EQUAL(FALSE, TimeService_Private_IsCallbackTime(alarm));
}

TEST(TimeService, SetMaxAlarms)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];
  PeriodicAlarmCallback callbackArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm(callbackArray[i], i*100+period);
  }

  // for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  // {
  //   TimeService_SetPeriodicAlarm(alarmArray[i], callbackArray[i], i*100+period);
  // }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkCallbackAndPeriod(alarmArray[i], callbackArray[i], i*100+period);
    checkCounterAndFlag(alarmArray[i], PA_INACTIVE, FALSE);
  }
}

TEST(TimeService, PutHolesInAlarmArray)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];
  PeriodicAlarmCallback callbackArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm(callback, period);
  }

  //Remove odd-numbered alarms
  for (int i = 1; i < MAX_PERIODIC_ALARMS; i += 2)
  {
    TimeService_RemovePeriodicAlarm(alarmArray[i]);
    checkCallbackAndPeriod(alarmArray[i], NULL, PA_UNUSED);
    checkCounterAndFlag(alarmArray[i], PA_UNUSED, FALSE);
  }

  //Check that even-numbered alarms aren't affected
  for (int i = 0; i < MAX_PERIODIC_ALARMS; i += 2)
  {
    checkCallbackAndPeriod(alarmArray[i], callback, period);
    checkCounterAndFlag(alarmArray[i], PA_INACTIVE, FALSE);
  }

  //Add odd-numbered alarms again
  for (int i = 1; i < MAX_PERIODIC_ALARMS; i += 2)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm(callback, period);
    checkCallbackAndPeriod(alarmArray[i], callback, period);
    checkCounterAndFlag(alarmArray[i], PA_INACTIVE, FALSE);
  }

  //TimeService should be maxed out
  POINTERS_EQUAL(NULL, TimeService_AddPeriodicAlarm(callback, period));
}

TEST(TimeService, SetCounter)
{
  int16_t testValue = 42;
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_Private_SetCounter(alarm, testValue);

  LONGS_EQUAL(testValue, TimeService_Private_GetCounter(alarm));
}

TEST(TimeService, IncrementCounter)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  //TODO activate
  TimeService_Private_SetCounter(alarm, 0);
  TimeService_Private_IncrementCounter(alarm);

  LONGS_EQUAL(1, TimeService_Private_GetCounter(alarm));
}

TEST(TimeService, CountersWontIncrementIfAlarmIsNotSet)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_Private_IncrementCounter(alarm);

  LONGS_EQUAL(PA_COUNTER_RESET_VALUE, TimeService_Private_GetCounter(alarm));
}

TEST(TimeService, NotCallbackTimeWhenCounterLessThanPeriod)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_TimerTick();

  LONGS_EQUAL(FALSE, TimeService_Private_IsCallbackTime(alarm));
}

TEST(TimeService, IsCallbackTimeWhenCounterEqualsPeriod)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_Private_SetCounter(alarm, period-1);
  TimeService_TimerTick();

  checkCounterAndFlag(alarm, PA_COUNTER_RESET_VALUE, TRUE);
}

TEST(TimeService, NoCallbackExecutedIfIsntTime)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_Private_SetCounter(alarm, 0);
  TimeService_TimerTick();

  TimeService_ServiceAllCallbacks();
}

TEST(TimeService, CallbackExecutedWhenItsTime)
{
  callback = callbackFunction;
  alarm = TimeService_AddPeriodicAlarm(callback, period);

  TimeService_Private_SetCounter(alarm, period-1);
  TimeService_TimerTick();

  mock().expectOneCall("callbackFunction");
  TimeService_ServiceAllCallbacks();
}

TEST(TimeService, ExecuteMultipleCallbacks)
{
  PeriodicAlarm alarm2;
  PeriodicAlarm alarm3;
  PeriodicAlarmCallback callback2;
  PeriodicAlarmCallback callback3;

  callback  = callbackFunction;
  callback2 = callbackFunction2;
  callback3 = callbackFunction3;
  alarm  = TimeService_AddPeriodicAlarm(callback,  period);
  alarm2 = TimeService_AddPeriodicAlarm(callback2, period);
  alarm3 = TimeService_AddPeriodicAlarm(callback3, period+1);

  TimeService_Private_SetCounter(alarm,  period-1);
  TimeService_Private_SetCounter(alarm2, period-1);
  TimeService_Private_SetCounter(alarm3, period-1);
  TimeService_TimerTick();

  mock().expectOneCall("callbackFunction");
  mock().expectOneCall("callbackFunction2");
  TimeService_ServiceAllCallbacks();
}

TEST(TimeService, CallbackFlagClearedAfterExecution)
{
  callback = callbackFunction;
  alarm = TimeService_AddPeriodicAlarm(callback, period);

  TimeService_Private_SetCounter(alarm, period-1);
  TimeService_TimerTick();

  mock().expectOneCall("callbackFunction");
  TimeService_ServiceAllCallbacks();
  TimeService_TimerTick();
  TimeService_ServiceAllCallbacks();
}
