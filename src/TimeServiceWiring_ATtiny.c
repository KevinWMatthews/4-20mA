#include "TimeServiceWiringHw.h"
#include "BitManip.h"
#include <avr/io.h>
#include <avr/interrupt.h>



void TimeServiceWiringHw_SetPrescaler(TimeService_PrescaleFactor prescaleFactor)
{
  SHIFT_AND_SET_BITMASK_TO(TCCR1B, prescaleFactor, BITMASK_TS_PRESCALE_FACTOR);
}

void TimeServiceWiringHw_SetTimerCompare(uint8_t timerCompareValue)
{
  OCR1C = timerCompareValue;
}

void TimeServiceWiringHw_ClearTimerOnMatch(BOOL clearOnMatchFlag)
{
  SHIFT_AND_SET_BITMASK_TO(TCCR1B, clearOnMatchFlag, BITMASK_TS_CLEAR_TIMER_ON_MATCH);
}

void TimeServiceWiringHw_SetTimerCompareInterrupt(BOOL enableInterrupt)
{
  SHIFT_AND_SET_BITMASK_TO(TIMSK, enableInterrupt, BITMASK_TS_COMPARE_INTERRUPT);
}
