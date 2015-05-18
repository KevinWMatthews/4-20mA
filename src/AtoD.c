#include "AtoD.h"
#include "ADC.h"

int8_t AtoD_StartConversion(void)
{
  if (Adc_IsAdcBusy())
  {
    return ATOD_BUSY;
  }

  Adc_StartConversion();
  return ATOD_CONVERSION_STARTED;
}

// Make sure you have unsigned 8-bit arguments!
//High Byte Low  Byte
//xxxx xx98 7654 3210
int16_t create10BitFromTwo8Bit(uint8_t highByte, uint8_t lowByte)
{
  highByte &= (0b11);     //keep only lowest two bits
  return (highByte << 8) + lowByte;
}

int8_t AtoD_Read(int16_t * reading)
{
  uint8_t high_register, low_register;

  if (Adc_IsAdcBusy())
  {
    return ATOD_BUSY;
  }
  if (!Adc_IsInterruptFlagSet())
  {
    return ATOD_INTERRUPT_FLAG_NOT_SET;
  }

  low_register = Adc_ReadDataRegister_Low();
  high_register = Adc_ReadDataRegister_High();
  *reading = create10BitFromTwo8Bit(high_register, low_register);
  Adc_ClearInterruptFlag();
  return ATOD_READ_SUCCESS;
}
