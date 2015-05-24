#include "LedNumber.h"
#include "LedDigit.h"
#include "DataTypes.h"

static int8_t * pinSelect;
static LedDigit ones;

void LedNumber_Create(int8_t * ledSelectPin)
{
  ones = LedDigit_Create();
  pinSelect = ledSelectPin;
  *pinSelect = PIN_OFF;
}

void LedNumber_Destroy(void)
{
  LedDigit_Destroy(&ones);
}

void LedNumber_ShowNumber(int16_t number)
{
  LedDigit_ShowDigit(ones, number);
  *pinSelect = PIN_ON;
}
