extern "C"
{
  #include "TimeService.h"
}

#include "TestHelper_TimeService.h"
#include "CppUTestExt/MockSupport.h"


//Public variables
callbackParameter structCallbackParameter;
int integerCallbackParameter;


//Sample real callbacks
void doubleIntegerParamemeter(void * params)
{
  int * iptr;

  if ( params == NULL )
  {
    integerCallbackParameter = 0; //kloodgy demonstration
    return;
  }
  iptr = (int*)params;
  *iptr *= 2;
}

void useStructParameter(void * params)
{
  callbackParameter * sptr;

  if ( params == NULL )
  {
    return;
  }
  sptr = (callbackParameter *)params;
  sptr->anInteger *= 2;
  sptr->aFloat *= 2.0;
}


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
  LONGS_EQUAL(executeNow, TimeService_Private_IsCallbackTime(self));
}
