extern "C"
{
  #include "TimeService.h"
  #include "TimeServiceWiring.h"
}

#include "TestHelper_TimeService.h"
//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_TimeService.h"



TEST_GROUP(TimeService)
{
  PeriodicAlarm alarm;
  PeriodicAlarmCallback callback;
  int16_t period;
  void * nullPointer;

  void setup()
  {
    period = 42;
    TimeService_Create();
    nullPointer = NULL;
  }

  void teardown()
  {
    TimeService_Destroy();
    mock().checkExpectations();
    mock().clear();
  }
};



//*******************//
//*** Unit Tests! ***//
//*******************//
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
  TimeService_ActivatePeriodicAlarm(NULL);
  TimeService_DeactivatePeriodicAlarm(NULL);
  TimeService_ServiceSingleCallback(NULL, NULL);
}


//Wiring
TEST(TimeService, HwSetup)
{
  mock().expectOneCall("TimeServiceWiring_HardwareSetup");
  TimeService_HwSetup();
}


//Add alarms
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


//Remove alarms
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

TEST(TimeService, PutHolesInAlarmArray)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];

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


//Destroy TimeService
TEST(TimeService, DestroyWhenSingleAlarm)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_Destroy();

  checkCallbackAndPeriod(alarm, NULL, PA_UNUSED);
  checkCounterAndFlag(alarm, PA_UNUSED, FALSE);
}

TEST(TimeService, DestroyWhenMaxAlarm)
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


//Activate alarms
TEST(TimeService, ActivateSinglePeriodicAlarm)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  checkCallbackAndPeriod(alarm, callback, period);
  checkCounterAndFlag(alarm, PA_COUNTER_RESET_VALUE, FALSE);
}

TEST(TimeService, ActivateMaxAlarms)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];
  PeriodicAlarmCallback callbackArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm(callbackArray[i], i*100+period);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    TimeService_ActivatePeriodicAlarm(alarmArray[i]);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkCallbackAndPeriod(alarmArray[i], callbackArray[i], i*100+period);
    checkCounterAndFlag(alarmArray[i], PA_COUNTER_RESET_VALUE, FALSE);
  }
}

TEST(TimeService, ActivateNonconsecutiveAlarms)
{
  PeriodicAlarm alarmArray[MAX_PERIODIC_ALARMS];
  PeriodicAlarmCallback callbackArray[MAX_PERIODIC_ALARMS];

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    alarmArray[i] = TimeService_AddPeriodicAlarm(callbackArray[i], i*100+period);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i += 2)
  {
    TimeService_ActivatePeriodicAlarm(alarmArray[i]);
  }

  for (int i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    checkCallbackAndPeriod(alarmArray[i], callbackArray[i], i*100+period);
    if (i % 2 == 0)
    {
      checkCounterAndFlag(alarmArray[i], PA_COUNTER_RESET_VALUE, FALSE);
    }
    else
    {
      checkCounterAndFlag(alarmArray[i], PA_INACTIVE, FALSE);
    }
  }
}


//Deactivate alarms
TEST(TimeService, DeactivateSinglePeriodicAlarm)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_DeactivatePeriodicAlarm(alarm);
  checkCallbackAndPeriod(alarm, callback, period);
  checkCounterAndFlag(alarm, PA_INACTIVE, FALSE);
}


//Counter
TEST(TimeService, CountersWontIncrementIfAlarmIsNotActivated)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_TimerTick();

  LONGS_EQUAL(PA_INACTIVE, TimeServicePrivate_GetCounter(alarm));
}

TEST(TimeService, CountersWontIncrementIfAlarmIsDeactivated)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_DeactivatePeriodicAlarm(alarm);

  TimeService_TimerTick();

  LONGS_EQUAL(PA_INACTIVE, TimeServicePrivate_GetCounter(alarm));
}

TEST(TimeService, IncrementCounter)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);

  TimeService_TimerTick();

  LONGS_EQUAL(1, TimeServicePrivate_GetCounter(alarm));
}

TEST(TimeService, TickSetsExecuteCallbackFlagAndResetsCounterWhenPeriodExpires)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeServicePrivate_SetCounter(alarm, period-1);

  TimeService_TimerTick();

  LONGS_EQUAL(PA_COUNTER_RESET_VALUE, TimeServicePrivate_GetCounter(alarm));
  LONGS_EQUAL(TRUE, TimeServicePrivate_GetExecuteCallbackFlag(alarm));
}

TEST(TimeService, TickSetsMultipleCallbackFlags)
{
  PeriodicAlarm alarm2;
  PeriodicAlarm alarm3;
  PeriodicAlarmCallback callback2;
  PeriodicAlarmCallback callback3;

  callback  = callbackFunction;
  callback2 = callbackFunction2;
  callback3 = callbackFunction3;
  alarm  = TimeService_AddPeriodicAlarm(callback,  period-1);
  alarm2 = TimeService_AddPeriodicAlarm(callback2, period-1);
  alarm3 = TimeService_AddPeriodicAlarm(callback3, period-1);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_ActivatePeriodicAlarm(alarm2);
  TimeService_ActivatePeriodicAlarm(alarm3);

  TimeServicePrivate_SetCounter(alarm,  period-1);
  TimeServicePrivate_SetCounter(alarm2, period-1);
  TimeServicePrivate_SetCounter(alarm3, period-1);

  TimeService_TimerTick();

  LONGS_EQUAL(PA_COUNTER_RESET_VALUE, TimeServicePrivate_GetCounter(alarm));
  LONGS_EQUAL(PA_COUNTER_RESET_VALUE, TimeServicePrivate_GetCounter(alarm2));
  LONGS_EQUAL(PA_COUNTER_RESET_VALUE, TimeServicePrivate_GetCounter(alarm3));
  LONGS_EQUAL(TRUE, TimeServicePrivate_GetExecuteCallbackFlag(alarm));
  LONGS_EQUAL(TRUE, TimeServicePrivate_GetExecuteCallbackFlag(alarm2));
  LONGS_EQUAL(TRUE, TimeServicePrivate_GetExecuteCallbackFlag(alarm3));
}


//Execute callback now flag
TEST(TimeService, NoCallbackExecutedIfIsntTime)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);

  TimeService_ServiceSingleCallback(alarm, nullPointer);
  //Mock will fail if callback is executed
}

TEST(TimeService, CallbackExecutedWhenItsTime)
{
  callback = callbackFunction;
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeServicePrivate_SetExecuteCallbackFlag(alarm, TRUE);

  mock().expectOneCall("callbackFunction")
        .withParameter("params", nullPointer);

  TimeService_ServiceSingleCallback(alarm, nullPointer);
  LONGS_EQUAL(FALSE, TimeServicePrivate_GetExecuteCallbackFlag(alarm));
}

TEST(TimeService, OnlyCallbacksWithFlagWillExecute)
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
  alarm3 = TimeService_AddPeriodicAlarm(callback3, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_ActivatePeriodicAlarm(alarm2);
  TimeService_ActivatePeriodicAlarm(alarm3);
  TimeServicePrivate_SetExecuteCallbackFlag(alarm, TRUE);
  TimeServicePrivate_SetExecuteCallbackFlag(alarm2, FALSE);
  TimeServicePrivate_SetExecuteCallbackFlag(alarm3, TRUE);

  mock().expectOneCall("callbackFunction")
        .withParameter("params", nullPointer);
  mock().expectOneCall("callbackFunction3")
        .withParameter("params", nullPointer);

  TimeService_ServiceSingleCallback(alarm, nullPointer);
  TimeService_ServiceSingleCallback(alarm2, nullPointer);
  TimeService_ServiceSingleCallback(alarm3, nullPointer);
}

TEST(TimeService, SeveralServicesDontDisruptCounter)
{
  callback = callbackFunction;
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeServicePrivate_SetCounter(alarm, period-11);
  TimeService_TimerTick();

  LONGS_EQUAL(period-10, TimeServicePrivate_GetCounter(alarm));
  TimeService_ServiceSingleCallback(alarm, nullPointer);
  LONGS_EQUAL(period-10, TimeServicePrivate_GetCounter(alarm));
  TimeService_ServiceSingleCallback(alarm, nullPointer);
  LONGS_EQUAL(period-10, TimeServicePrivate_GetCounter(alarm));
}
