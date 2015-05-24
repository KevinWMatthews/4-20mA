#include "LedNumber.h"
#include "DataTypes.h"

static int8_t * pinSelect;

void LedNumber_Create(int8_t * ledSelectPin)
{
  pinSelect = ledSelectPin;
  *pinSelect = PIN_OFF;
}

void LedNumber_Destroy(void)
{

}
