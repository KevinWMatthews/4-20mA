#include "TimeServiceWiring.h"
#include "BitManip.h"
#include <avr/io.h>
#include <avr/interrupt.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Edit here to change hardware setup! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TimeServiceWiring_HwSetup(void)
{
  TimeServiceWiring_SetTimerBitWidth(TS_EIGHT_BIT);
  TimeServiceWiring_ClearTimerOnMatch(TRUE);
  TimeServiceWiring_SetTimerCompareValue0A(125);
  TimeServiceWiring_SetTimerCompareInterrupt0A(TRUE);
  TimeServiceWiring_SetPrescaleFactor(TS_PRESCALE_FACTOR_8);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Hardware setup modification should not cause changes below this point! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//Unless you're adding options that I haven't used yet.



void TimeServiceWiring_SetTimerBitWidth(TimeService_TimerBitWidth timerBitWidth)
{
  SHIFT_AND_SET_BITMASK_TO(TCCR0A, timerBitWidth, BITMASK_TS_TIMER_BIT_WIDTH);
}

void TimeServiceWiring_SetPrescaleFactor(TimeService_PrescaleFactor prescaleFactor)
{
  SHIFT_AND_SET_BITMASK_TO(TCCR0B, prescaleFactor, BITMASK_TS_PRESCALE_FACTOR);
}

void TimeServiceWiring_SetTimerCompareValue0A(uint8_t timerCompareValue)
{
  OCR0A = timerCompareValue;
}

void TimeServiceWiring_ClearTimerOnMatch(BOOL clearOnMatchFlag)
{
  SHIFT_AND_SET_BITMASK_TO(TCCR0A, clearOnMatchFlag, BITMASK_TS_CLEAR_TIMER_ON_MATCH);
}

void TimeServiceWiring_SetTimerCompareInterrupt0A(BOOL enableInterrupt)
{
  SHIFT_AND_SET_BITMASK_TO(TIMSK, enableInterrupt, BITMASK_TS_COMPARE_INTERRUPT_0A);
}
