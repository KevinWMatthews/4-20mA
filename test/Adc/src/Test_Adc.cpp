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
    Adc_MapMemory(&adcsr, &admux, &adch, &adcl);
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
  uint8_t expected = 0xff;
  admux = 0xff;
  //ADC_AVCC = 0b00, so clear its bits
  CBI(expected, REFS1);
  CBI(expected, REFS0);
  Adc_Private_SelectReferenceVoltage(ADC_AVCC);
  CHECK_TRUE(IFBITMASK(expected, admux, 0xff));
}

TEST(Adc, SelectResultAdjust)
{
  uint8_t expected = 0xff;
  admux = 0xff;
  //ADC_RIGHT_ADJUST= 0b0, so clear its bit
  CBI(expected, ADLAR);
  Adc_Private_SelectResultAdjust(ADC_RIGHT_ADJUST);
  CHECK_TRUE(IFBITMASK(expected, admux, 0xff));
}

TEST(Adc, SelectInputAndGain)
{
  uint8_t expected = 0xff;
  admux = 0xff;
  //ADC_SINGLE_ENDED_ADC0 = 0b00000, so clear its bits
  CBI(expected, MUX4);
  CBI(expected, MUX3);
  CBI(expected, MUX2);
  CBI(expected, MUX1);
  CBI(expected, MUX0);
  Adc_Private_SelectInputAndGain(ADC_SINGLE_ENDED_ADC0);
  CHECK_TRUE(IFBITMASK(expected, admux, 0xff));
}

TEST(Adc, SetPrescaleFactor)
{
  uint8_t expected = 0xff;
  adcsr = 0xff;
  CBI(expected, ADPS2);
  CBI(expected, ADPS1);
  CBI(expected, ADPS0);
  Adc_Private_SelectPrescaleFactor(ADC_PRESCALE_FACTOR_0);
  CHECK_TRUE(IFBITMASK(expected, adcsr, 0xff));
}

TEST(Adc, Init)
{
  uint8_t expected_admux = 0, expected_adcsr = 0;
  CBI(expected_admux, REFS1);
  CBI(expected_admux, REFS0);
  CBI(expected_admux, ADLAR);
  CBI(expected_admux, MUX4);
  CBI(expected_admux, MUX3);
  CBI(expected_admux, MUX2);
  CBI(expected_admux, MUX1);
  CBI(expected_admux, MUX0);
  CBI(expected_adcsr, ADPS2);
  CBI(expected_adcsr, ADPS1);
  SBI(expected_adcsr, ADPS0);
  Adc_Init();
  CHECK_TRUE(IFBITMASK(expected_admux, admux, 0xff));
  CHECK_TRUE(IFBITMASK(expected_adcsr, adcsr, 0x07));
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
