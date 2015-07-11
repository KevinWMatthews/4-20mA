extern "C"
{
  #include "TimeService.h"
}

#include "TestHelper_TimeService.h"
#include "CppUTestExt/MockSupport.h"



//Mock callbacks
void callbackFunction(void * params)
{
  mock().actualCall("callbackFunction")
        .withParameter("params", params);
}

void callbackFunction2(void * params)
{
  mock().actualCall("callbackFunction2")
        .withParameter("params", params);
}

void callbackFunction3(void * params)
{
  mock().actualCall("callbackFunction3")
        .withParameter("params", params);
}



//Condition checks
void checkCallbackAndPeriod(PeriodicAlarm alarm, PeriodicAlarmCallback callbackFunction, int16_t alarmPeriod)
{
  POINTERS_EQUAL(callbackFunction, TimeService_Private_GetCallback(alarm));
  LONGS_EQUAL(alarmPeriod, TimeService_Private_GetPeriod(alarm));
}

void checkCounterAndFlag(PeriodicAlarm self, int16_t counter, BOOL executeNow)
{
  LONGS_EQUAL(counter, TimeService_Private_GetCounter(self));
  LONGS_EQUAL(executeNow, TimeService_Private_GetExecuteCallbackFlag(self));
}
