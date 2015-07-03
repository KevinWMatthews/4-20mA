#ifndef LedNumber_H_
#define LedNumber_H_

#include "LedDigit.h"
#include "LedNumberWiring.h"



//******************//
//*** Data types ***//
//******************//
typedef enum
{
  LED_NONE        = -1,
  LED_UNITS       =  0,
  LED_TENS        =  1,
  LED_HUNDREDS    =  2,
  LED_THOUSANDS   =  3,
  LED_UPPER_BOUND =  4
} LedNumber_Place;

typedef struct LedNumberStruct * LedNumber;

#define LEDNUMBER_NULL_POINTER  -1
#define LEDNUMBER_INVALID_PLACE -2


//************************//
//*** Public Functions ***//
//************************//
void LedNumber_HwSetup(void);

LedNumber LedNumber_Create(LedNumber_Place largestDigit);
int8_t LedNumber_AddLedDigit(LedNumber self, LedDigit digit, LedNumber_Place place);
void LedNumber_Destroy(LedNumber * self);

void LedNumber_SetNumber(LedNumber self, int16_t number);
void LedNumber_ClearNumber(LedNumber self);

void LedNumber_ShowNumber(LedNumber self);
void LedNumber_TurnOff(LedNumber self);


int16_t getDigitFromNumber(int16_t number, LedNumber_Place place);

#endif
