#include "Adc.h"
#include "AdcWiring.h"

void Adc_Setup(void)
{
  AdcWiring_Init();
  AdcWiring_Enable();
  AdcWiring_FirstConversion();
}

int8_t Adc_StartConversion(void)
{
  if (AdcWiring_IsAdcBusy())
  {
    return ADC_CONVERSION_BUSY;
  }

  AdcWiring_StartConversion();
  return ADC_CONVERSION_STARTED;
}

// Make sure you have unsigned 8-bit arguments!
//High Byte Low  Byte
//xxxx xx98 7654 3210
int16_t create10BitFromTwo8Bit(uint8_t highByte, uint8_t lowByte)
{
  highByte &= (0b11);     //keep only lowest two bits
  return (highByte << 8) + lowByte;
}

int8_t Adc_Read(int16_t * adcReading)
{
  uint8_t high_register, low_register;

  if (AdcWiring_IsAdcBusy())
  {
    return ADC_READ_BUSY;
  }
  // if (!AdcWiring_IsInterruptFlagSet())
  // {
  //   return ADC_INTERRUPT_FLAG_NOT_SET;
  // }

  low_register = AdcWiring_ReadDataRegister_Low();
  high_register = AdcWiring_ReadDataRegister_High();
  *adcReading = create10BitFromTwo8Bit(high_register, low_register);
  AdcWiring_ClearInterruptFlag();
  return ADC_READ_SUCCESS;
}
