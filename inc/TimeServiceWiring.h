#ifndef TimeServiceWiring_H
#define TimeServiceWiring_H

#include "DataTypes.h"



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



//************************//
//*** Public Functions ***//
//************************//
void TimeServiceWiring_HwSetup(void);


void TimeServiceWiringPrivate_SetPrescaler(TimeService_PrescaleFactor);
void TimeServiceWiringPrivate_SetTimerCompare(uint8_t);
void TimeServiceWiringPrivate_ClearTimerOnMatch(BOOL);


#endif
