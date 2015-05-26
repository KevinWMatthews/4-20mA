#ifndef LedDigit_H_
#define LedDigit_H_

#include <stdint.h>

typedef struct LedDigitStruct * LedDigit;

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

typedef struct
{
  int8_t * pin1;
  int8_t * pin2;
  int8_t * pin4;
  int8_t * pin5;
  int8_t * pin6;
  int8_t * pin7;
  int8_t * pin9;
  int8_t * pin10;
} LedDigit_DataPins;

LedDigit LedDigit_Create(LedDigit_DataPins * dataPins);
void LedDigit_Destroy(LedDigit * self);
void LedDigit_ShowDigit(LedDigit self, LedDigit_DisplayDigit number);
void LedDigit_ShowDecimal(LedDigit self);
void LedDigit_ClearDigit(LedDigit self);
void LedDigit_ClearDecimal(LedDigit self);
void LedDigit_ClearAll(LedDigit self);

#endif
