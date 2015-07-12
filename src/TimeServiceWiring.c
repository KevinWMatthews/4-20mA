#include "TimeServiceWiring.h"
#include "BitManip.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void TimeServiceWiringPrivate_SetPrescaler(TimeService_PrescaleFactor prescaleFactor)
{
  SET_BITMASK_SHIFT_VALUE(TCCR1B, prescaleFactor, BITMASK_TS_PRESCALE_FACTOR, LSB_TS_PRESCALE_FACTOR);
}

void TimeServiceWiringPrivate_SetTimerCompare(uint8_t timerCompareValue)
{
  OCR1C = timerCompareValue;
}

void TimeServiceWiringPrivate_ClearTimerOnMatch(BOOL clearOnMatchFlag)
{
  SET_BITMASK_SHIFT_VALUE(TCCR1B, clearOnMatchFlag, BITMASK_TS_CLEAR_TIMER_ON_MATCH, LSB_TS_CLEAR_TIMER_ON_MATCH);
}
