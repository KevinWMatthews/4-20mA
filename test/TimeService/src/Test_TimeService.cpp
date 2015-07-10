extern "C"
{
  #include "TimeService.h"
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

  POINTERS_EQUAL(NULL, TimeService_Private_GetCallback(NULL));
  LONGS_EQUAL(PA_NULL_POINTER, TimeService_Private_GetPeriod(NULL));
  TimeService_Private_SetCounter(NULL, 666);
  LONGS_EQUAL(PA_NULL_POINTER, TimeService_Private_GetCounter(NULL));
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

TEST(TimeService, AddRemove_PutHolesInAlarmArray)
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

TEST(TimeService, DeactivateSinglePeriodicAlarm)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_DeactivatePeriodicAlarm(alarm);
  checkCallbackAndPeriod(alarm, callback, period);
  checkCounterAndFlag(alarm, PA_INACTIVE, FALSE);
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
  TimeService_ActivatePeriodicAlarm(alarm);

  TimeService_TimerTick();

  LONGS_EQUAL(1, TimeService_Private_GetCounter(alarm));
}

TEST(TimeService, CountersWontIncrementIfAlarmIsNotActivated)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_TimerTick();

  LONGS_EQUAL(PA_INACTIVE, TimeService_Private_GetCounter(alarm));
}

TEST(TimeService, CountersWontIncrementIfAlarmIsDeactivated)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_DeactivatePeriodicAlarm(alarm);

  TimeService_TimerTick();

  LONGS_EQUAL(PA_INACTIVE, TimeService_Private_GetCounter(alarm));
}

TEST(TimeService, NoCallbackExecutedIfIsntTime)
{
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_TimerTick();

  TimeService_ServiceSingleCallback(alarm, nullPointer);
}

TEST(TimeService, CallbackExecutedWhenItsTime)
{
  callback = callbackFunction;
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_Private_SetCounter(alarm, period-1);

  mock().expectOneCall("callbackFunction")
        .withParameter("params", nullPointer);

  TimeService_TimerTick();
  TimeService_ServiceSingleCallback(alarm, nullPointer);
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
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_ActivatePeriodicAlarm(alarm2);
  TimeService_ActivatePeriodicAlarm(alarm3);
  TimeService_Private_SetCounter(alarm,  period-1);
  TimeService_Private_SetCounter(alarm2, period-1);
  TimeService_Private_SetCounter(alarm3, period-1);

  mock().expectOneCall("callbackFunction")
        .withParameter("params", nullPointer);
  mock().expectOneCall("callbackFunction2")
        .withParameter("params", nullPointer);

  TimeService_TimerTick();
  TimeService_ServiceSingleCallback(alarm, nullPointer);
  TimeService_ServiceSingleCallback(alarm2, nullPointer);
  TimeService_ServiceSingleCallback(alarm3, nullPointer);
}

TEST(TimeService, CallbackFlagClearedAfterExecution)
{
  callback = callbackFunction;
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_Private_SetCounter(alarm, period-1);

  mock().expectOneCall("callbackFunction")
        .withParameter("params", nullPointer);

  TimeService_TimerTick();
  TimeService_ServiceSingleCallback(alarm, nullPointer);
  TimeService_TimerTick();
  TimeService_ServiceSingleCallback(alarm, nullPointer);
}

TEST(TimeService, SeveralServicesDontDisruptCounter)
{
  callback = callbackFunction;
  alarm = TimeService_AddPeriodicAlarm(callback, period);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_Private_SetCounter(alarm, period-11);
  TimeService_TimerTick();

  LONGS_EQUAL(period-10, TimeService_Private_GetCounter(alarm));
  TimeService_ServiceSingleCallback(alarm, nullPointer);
  LONGS_EQUAL(period-10, TimeService_Private_GetCounter(alarm));
  TimeService_ServiceSingleCallback(alarm, nullPointer);
  LONGS_EQUAL(period-10, TimeService_Private_GetCounter(alarm));
}

//Maybe this isn't the best test, but I'm just learning
//We should test the callback function separately
//This is to demonstrate that NULL will actually reach the callback
TEST(TimeService, CallbackMustHandleNullParameter)
{
  callback = doubleIntegerParamemeter;
  alarm = TimeService_AddPeriodicAlarm(callback, 50);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_Private_SetCounter(alarm, 49);
  TimeService_TimerTick();
  TimeService_ServiceSingleCallback(alarm, nullPointer);
  LONGS_EQUAL(0, integerCallbackParameter);
}

TEST(TimeService, CallbackWithIntegerParameter)
{
  callback = doubleIntegerParamemeter;
  integerCallbackParameter = 42;

  alarm = TimeService_AddPeriodicAlarm(callback, 50);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_Private_SetCounter(alarm, 49);
  TimeService_TimerTick();
  TimeService_ServiceSingleCallback(alarm, (void*)&integerCallbackParameter);
  LONGS_EQUAL(84, integerCallbackParameter);
}

TEST(TimeService, CallbackWithStructParameter)
{
  callback = useStructParameter;
  structCallbackParameter.anInteger = 42;
  structCallbackParameter.aFloat = 5.5;
  alarm = TimeService_AddPeriodicAlarm(callback, 1);
  TimeService_ActivatePeriodicAlarm(alarm);
  TimeService_TimerTick();
  TimeService_ServiceSingleCallback(alarm, (void*)&structCallbackParameter);
  LONGS_EQUAL(84, structCallbackParameter.anInteger);
  DOUBLES_EQUAL(11.0, structCallbackParameter.aFloat, 0.1);
}
