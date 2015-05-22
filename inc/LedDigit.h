#ifndef LedDigit_H_
#define LedDigit_H_

#include <stdint.h>

typedef struct LedDigitStruct * LedDigit;

typedef enum
{
  //Pins 3 and 8 are not available for use
  PIN1 = 0,
  PIN2 = 1,
  PIN4 = 2,
  PIN5 = 3,
  PIN6 = 4,
  PIN7 = 5,
  PIN9 = 6,
  PIN10 = 7,
  PIN_MAX = 8
} LedDigit_PinNumber;

typedef enum
{
  NOTHING = -1,
  ZERO = 0,
  ONE = 1,
  TWO = 2,
  THREE = 3,
  FOUR = 4,
  FIVE = 5,
  SIX = 6,
  SEVEN = 7,
  EIGHT = 8,
  NINE = 9
} LedDigit_DisplayDigit;

LedDigit LedDigit_Create(void);
void LedDigit_Destroy(LedDigit * self);
void LedDigit_WirePin(LedDigit self, LedDigit_PinNumber pinNumber, int8_t * pinAddress);
void LedDigit_ShowDigit(LedDigit self, LedDigit_DisplayDigit number);
void LedDigit_ShowDecimal(LedDigit self);
void LedDigit_Clear(LedDigit self);

#endif
