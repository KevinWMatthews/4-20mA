extern "C"
{
  #include "Adc.h"  //Code under test
  #include "BitManip.h"
  #include <avr/io.h>
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_Adc.h"

uint8_t adcsr;
uint8_t admux;
uint8_t adch;
uint8_t adcl;

TEST_GROUP(Adc)
{
  void setup()
  {
    adcsr = 0;
    admux = 0;
    adch = 0;
    adcl = 0;
    Adc_Init(&adcsr, &admux, &adch, &adcl);
  }

  void teardown()
  {
  }
};

//Wait, this may not be true...
TEST(Adc, RegistersZeroAfterInit)
{
  LONGS_EQUAL(0, adcsr);
  LONGS_EQUAL(0, admux);
  LONGS_EQUAL(0, adch);
  LONGS_EQUAL(0, adcl);
}

TEST(Adc, SelectReferenceVoltage)
{
  uint8_t bitmask;
  SBI(bitmask, REFS1);
  SBI(bitmask, REFS0);
  Adc_SelectReferenceVoltage(ADC_AVCC);
  CHECK_TRUE(IFBITMASK(admux, ADC_AVCC<<REFS0, bitmask));
}

TEST(Adc, SelectResultAdjust)
{
  SBI(admux, ADLAR);
  Adc_SelectResultAdjust(ADC_RIGHT_ADJUST);
  CHECK_FALSE(IFBIT(admux, ADLAR));
}

TEST(Adc, SelectInputAndGain)
{
  uint8_t bitmask;
  SBI(bitmask, MUX4);
  SBI(bitmask, MUX3);
  SBI(bitmask, MUX2);
  SBI(bitmask, MUX1);
  SBI(bitmask, MUX0);
  admux = bitmask;
  Adc_SelectInputAndGain(ADC_SINGLE_ENDED_ADC0);
  CHECK_TRUE(IFBITMASK(admux, ADC_SINGLE_ENDED_ADC0<<MUX0, bitmask));
}

TEST(Adc, SetPrescaleFactor)
{
  uint8_t bitmask;
  SBI(bitmask, ADPS2);
  SBI(bitmask, ADPS1);
  SBI(bitmask, ADPS0);
  adcsr = bitmask;
  Adc_SetPrescaleFactor(ADC_PRESCALE_FACTOR_2);
  CHECK_TRUE(IFBITMASK(adcsr, ADC_PRESCALE_FACTOR_2<<ADPS0, bitmask));
}

TEST(Adc, Enable)
{
  Adc_Enable();
  CHECK_TRUE(IFBIT(adcsr, ADEN));
}

TEST(Adc, FirstConversion)
{
  Adc_FirstConversion();
  CHECK_TRUE(IFBIT(adcsr, ADSC));
}

TEST(Adc, IsAdcBusy)
{
  CHECK_FALSE(Adc_IsAdcBusy());
  SBI(adcsr, ADSC);
  CHECK_TRUE(Adc_IsAdcBusy());
}

TEST(Adc, StartConversion)
{
  Adc_StartConversion();
  CHECK_TRUE(IFBIT(adcsr, ADSC));
}

TEST(Adc, Adc_IsInterruptFlagSet)
{
  CHECK_FALSE(Adc_IsInterruptFlagSet());
  SBI(adcsr, ADIF);
  CHECK_TRUE(Adc_IsInterruptFlagSet());
}

TEST(Adc, Adc_ClearInterruptFlag)
{
  Adc_ClearInterruptFlag();
  //Seems counterintuitive, but we write 1 to clear the flag. HW takes care of the rest.
  CHECK_TRUE(Adc_IsInterruptFlagSet());
}

TEST(Adc, ReadHighRegister_ReadZero)
{
  LONGS_EQUAL(0, Adc_ReadDataRegister_High());
}

TEST(Adc, ReadLowRegister_ReadZero)
{
  LONGS_EQUAL(0, Adc_ReadDataRegister_Low());
}

TEST(Adc, ReadHighRegister_ReadMax)
{
  adch = 0xFF;
  LONGS_EQUAL(0b11, Adc_ReadDataRegister_High());
}

TEST(Adc, ReadLowRegister_ReadMax)
{
  adcl = 0xFF;
  LONGS_EQUAL(0xFF, Adc_ReadDataRegister_Low());
}
