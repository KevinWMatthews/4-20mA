extern "C"
{
  #include "Adc.h"  //Code under test
  #include "BitManip.h"
  #include <avr/io.h>
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_Adc.h"



TEST_GROUP(Adc)
{
  void setup()
  {
    ADCSR = 0;
    ADMUX = 0;
    ADCH = 0;
    ADCL = 0;
  }

  void teardown()
  {
  }
};

//Wait, this may not be true...
TEST(Adc, RegistersZeroAfterInit)
{
  LONGS_EQUAL(0, ADCSR);
  LONGS_EQUAL(0, ADMUX);
  LONGS_EQUAL(0, ADCH);
  LONGS_EQUAL(0, ADCL);
}

TEST(Adc, SelectReferenceVoltage)
{
  uint8_t expected = 0xff;
  ADMUX = 0xff;
  //ADC_AVCC = 0b00, so clear its bits
  CBI(expected, REFS1);
  CBI(expected, REFS0);
  Adc_Private_SelectReferenceVoltage(ADC_AVCC);
  CHECK_TRUE(IFBITMASK(expected, ADMUX, 0xff));
}

TEST(Adc, SelectResultAdjust)
{
  uint8_t expected = 0xff;
  ADMUX = 0xff;
  //ADC_RIGHT_ADJUST= 0b0, so clear its bit
  CBI(expected, ADLAR);
  Adc_Private_SelectResultAdjust(ADC_RIGHT_ADJUST);
  CHECK_TRUE(IFBITMASK(expected, ADMUX, 0xff));
}

TEST(Adc, SelectInputAndGain)
{
  uint8_t expected = 0xff;
  ADMUX = 0xff;
  //ADC_SINGLE_ENDED_ADC0 = 0b00000, so clear its bits
  CBI(expected, MUX4);
  CBI(expected, MUX3);
  CBI(expected, MUX2);
  CBI(expected, MUX1);
  CBI(expected, MUX0);
  Adc_Private_SelectInputAndGain(ADC_SINGLE_ENDED_ADC0);
  CHECK_TRUE(IFBITMASK(expected, ADMUX, 0xff));
}

TEST(Adc, SetPrescaleFactor)
{
  uint8_t expected = 0xff;
  ADCSR = 0xff;
  CBI(expected, ADPS2);
  CBI(expected, ADPS1);
  CBI(expected, ADPS0);
  Adc_Private_SelectPrescaleFactor(ADC_PRESCALE_FACTOR_0);
  CHECK_TRUE(IFBITMASK(expected, ADCSR, 0xff));
}

TEST(Adc, Init)
{
  uint8_t expected_ADMUX = 0, expected_ADCSR = 0;
  CBI(expected_ADMUX, REFS1);
  CBI(expected_ADMUX, REFS0);
  CBI(expected_ADMUX, ADLAR);
  CBI(expected_ADMUX, MUX4);
  CBI(expected_ADMUX, MUX3);
  CBI(expected_ADMUX, MUX2);
  CBI(expected_ADMUX, MUX1);
  CBI(expected_ADMUX, MUX0);
  CBI(expected_ADCSR, ADPS2);
  CBI(expected_ADCSR, ADPS1);
  SBI(expected_ADCSR, ADPS0);
  Adc_Init();
  CHECK_TRUE(IFBITMASK(expected_ADMUX, ADMUX, 0xff));
  CHECK_TRUE(IFBITMASK(expected_ADCSR, ADCSR, 0x07));
}

TEST(Adc, Enable)
{
  Adc_Enable();
  CHECK_TRUE(IFBIT(ADCSR, ADEN));
}

TEST(Adc, FirstConversion)
{
  Adc_FirstConversion();
  CHECK_TRUE(IFBIT(ADCSR, ADSC));
}

TEST(Adc, IsAdcBusy)
{
  CHECK_FALSE(Adc_IsAdcBusy());
  SBI(ADCSR, ADSC);
  CHECK_TRUE(Adc_IsAdcBusy());
}

TEST(Adc, StartConversion)
{
  Adc_StartConversion();
  CHECK_TRUE(IFBIT(ADCSR, ADSC));
}

TEST(Adc, Adc_IsInterruptFlagSet)
{
  CHECK_FALSE(Adc_IsInterruptFlagSet());
  SBI(ADCSR, ADIF);
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
  ADCH = 0xFF;
  LONGS_EQUAL(0b11, Adc_ReadDataRegister_High());
}

TEST(Adc, ReadLowRegister_ReadMax)
{
  ADCL = 0xFF;
  LONGS_EQUAL(0xFF, Adc_ReadDataRegister_Low());
}
