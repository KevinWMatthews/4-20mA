#include "TimeServiceWiring.h"
#include "BitManip.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void TimeServiceWiringPrivate_SetPrescaler(TimeService_PrescaleFactor prescaleFactor)
{
  CLEAR_BITMASK(TCCR1B, BITMASK_TS_PRESCALE_FACTOR);
  SET_BITMASK_SHIFT(TCCR1B, prescaleFactor, LSB_TS_PRESCALE_FACTOR, BITMASK_TS_PRESCALE_FACTOR);
  // TCCR1B |= (prescaleFactor << LSB_TS_PRESCALE_FACTOR) & BITMASK_TS_PRESCALE_FACTOR;
}

void TimeServiceWiringPrivate_SetTimerCompare(uint8_t timerCompareValue)
{
  OCR1C = timerCompareValue;
}

void TimeServiceWiringPrivate_ClearTimerOnMatch(BOOL clearOnMatchFlag)
{
  TCCR1B &= ~BITMASK_TS_CLEAR_TIMER_ON_MATCH;
  TCCR1B |= (clearOnMatchFlag << LSB_TS_CLEAR_TIMER_ON_MATCH) & BITMASK_TS_CLEAR_TIMER_ON_MATCH;
}
