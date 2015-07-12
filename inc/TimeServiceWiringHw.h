#ifndef TimeServiceWiringHw_H
#define TimeServiceWiringHw_H

#include "TimeServiceWiring.h"



//********************//
//*** Setup Values ***//
//********************//
typedef enum
{
  TS_TIMER_STOPPED      = 0b0000,
  TS_PRESCALE_FACTOR_64 = 0b0111
} TimeService_PrescaleFactor;

#define BITMASK_TS_PRESCALE_FACTOR ((1<<CS10) | (1<<CS11)| (1<<CS12)| (1<<CS13))
#define LSB_TS_PRESCALE_FACTOR CS10

#define BITMASK_TS_CLEAR_TIMER_ON_MATCH (1<<CTC1)
#define LSB_TS_CLEAR_TIMER_ON_MATCH CTC1

#define BITMASK_TS_COMPARE_INTERRUPT (1<<OCIE1A)
#define LSB_TS_COMPARE_INTERRUPT OCIE1A

void TimeServiceWiringHw_SetPrescaler(TimeService_PrescaleFactor);
void TimeServiceWiringHw_SetTimerCompare(uint8_t);
void TimeServiceWiringHw_ClearTimerOnMatch(BOOL);
void TimeServiceWiringHw_SetTimerCompareInterrupt(BOOL);



#endif
