extern "C"
{
  #include "TimeServiceWiringHw.h"
}
#include "CppUTestExt/MockSupport.h"


void TimeServiceWiringHw_SetPrescaler(TimeService_PrescaleFactor prescaleFactor)
{
  mock().actualCall("TimeServiceWiringHw_SetPrescaler")
        .withParameter("prescaleFactor", prescaleFactor);
}

void TimeServiceWiringHw_SetTimerCompare(uint8_t timerCompareValue)
{
  mock().actualCall("TimeServiceWiringHw_SetTimerCompare")
        .withParameter("timerCompareValue", timerCompareValue);
}

void TimeServiceWiringHw_ClearTimerOnMatch(BOOL clearOnMatchFlag)
{
  mock().actualCall("TimeServiceWiringHw_ClearTimerOnMatch")
        .withParameter("clearOnMatchFlag", clearOnMatchFlag);
}

void TimeServiceWiringHw_SetTimerCompareInterrupt(BOOL enableInterrupt)
{
  mock().actualCall("TimeServiceWiringHw_SetTimerCompareInterrupt")
        .withParameter("enableInterrupt", enableInterrupt);
}
