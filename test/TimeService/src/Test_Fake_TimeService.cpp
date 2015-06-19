extern "C"
{
  #include "Fake_TimeService.h"
  #include "TimeService.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_Fake_TimeService.h"


void callbackFunction(void)
{
  mock().actualCall("callbackFunction");
}

TEST_GROUP(Fake_TimeService)
{
  PeriodicAlarm alarm;
  PeriodicCallback callback;

  void setup()
  {
    callback = callbackFunction;
    //Substitute our fake functions for the real ones
    //Rather than manually saving and restoring the pointer,
    //use CppUTest's built-in macro (it automatically restores the pointer!)
    UT_PTR_SET(TimeService_GetCounter, Fake_TimeService_GetCounter);
    UT_PTR_SET(TimeService_IncrementCounter, Fake_TimeService_IncrementCounter);
    UT_PTR_SET(TimeService_ResetCounter, Fake_TimeService_ResetCounter);

    TimeService_Create();
    Fake_TimeService_Create();
    alarm = TimeService_AddPeriodicAlarm();
  }

  void teardown()
  {
    TimeService_Destroy();
    Fake_TimeService_Destroy();
    mock().checkExpectations();
    mock().clear();
  }
};

TEST(Fake_TimeService, FakeCounterUnusedAfterAdd)
{
  LONGS_EQUAL(0, TimeService_GetCounter(alarm));
}

TEST(Fake_TimeService, SetFakeCounter)
{
  int16_t testValue = 42;
  Fake_TimeService_SetCounter(alarm, testValue);
  LONGS_EQUAL(testValue, TimeService_GetCounter(alarm));
}

TEST(Fake_TimeService, IncrementFakeCounter)
{
  TimeService_IncrementCounter(alarm);
  LONGS_EQUAL(1, TimeService_GetCounter(alarm));
}

TEST(Fake_TimeService, NotCallbackTimeWhenCounterLessThanPeriod)
{
  TimeService_SetPeriodicAlarm(alarm, callback, 42);
  TimeService_InterruptRoutine(alarm);

  LONGS_EQUAL(FALSE, TimeService_IsCallbackTime(alarm));
}

TEST(Fake_TimeService, IsCallbackTimeWhenCounterEqualsPeriod)
{
  TimeService_SetPeriodicAlarm(alarm, callback, 42);
  Fake_TimeService_SetCounter(alarm, 41);
  TimeService_InterruptRoutine(alarm);

  LONGS_EQUAL(0, TimeService_GetCounter(alarm));
  LONGS_EQUAL(TRUE, TimeService_IsCallbackTime(alarm));
}

TEST(Fake_TimeService, NoCallbackExecutedIfIsntTime)
{
  TimeService_SetPeriodicAlarm(alarm, callback, 42);
  Fake_TimeService_SetCounter(alarm, 0);
  TimeService_InterruptRoutine(alarm);

  TimeService_ServiceAllCallbacks();
}

TEST(Fake_TimeService, CallbackExecutedWhenItsTime)
{
  TimeService_SetPeriodicAlarm(alarm, callback, 42);
  Fake_TimeService_SetCounter(alarm, 41);
  TimeService_InterruptRoutine(alarm);

  mock().expectOneCall("callbackFunction");
  TimeService_ServiceAllCallbacks();
}
