#ifndef TimeServiceWiring_H
#define TimeServiceWiring_H

#include "DataTypes.h"

//Currently rigged up for the ATtiny861

//************************//
//*** Public Functions ***//
//************************//
void TimeServiceWiring_HardwareSetup(void);



//*******************************************//
//*** Private Functions with Setup Values ***//
//*******************************************//
typedef enum
{
  TS_EIGHT_BIT   = 0,
  TS_SIXTEEN_BIT = 1
} TimeService_TimerBitWidth;
#define BITMASK_TS_TIMER_BIT_WIDTH (1<<TCW0)
void TimeServiceWiring_SetTimerBitWidth(TimeService_TimerBitWidth);

#define BITMASK_TS_CLEAR_TIMER_ON_MATCH (1<<CTC0)
void TimeServiceWiring_ClearTimerOnMatch(BOOL);

typedef enum
{
  TS_TIMER_STOPPED      = 0b000,
  TS_PRESCALE_FACTOR_8  = 0b010,
  TS_EXTERNAL_T0_RISING = 0b111
} TimeService_PrescaleFactor;
#define BITMASK_TS_PRESCALE_FACTOR ((1<<CS02) | (1<<CS01) | (1<<CS00))
void TimeServiceWiring_SetPrescaleFactor(TimeService_PrescaleFactor);

void TimeServiceWiring_SetTimerCompareValue0A(uint8_t);

#define BITMASK_TS_COMPARE_INTERRUPT_0A (1<<OCIE0A)
void TimeServiceWiring_SetTimerCompareInterrupt0A(BOOL);



#endif
