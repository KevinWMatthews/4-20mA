#include "TimeServiceWiring.h"
#include "TimeServiceWiringHw.h"

void TimeServiceWiring_HwSetup(void)
{
  TimeServiceWiringHw_SetPrescaler(TS_PRESCALE_FACTOR_64);
  TimeServiceWiringHw_SetTimerCompare(125);
  TimeServiceWiringHw_ClearTimerOnMatch(TRUE);
  TimeServiceWiringHw_SetTimerCompareInterrupt(TRUE);
}
