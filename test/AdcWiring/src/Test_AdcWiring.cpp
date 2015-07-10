extern "C"
{
  #include "AdcWiring.h"  //Code under test
  #include "BitManip.h"
  #include <avr/io.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_AdcWiring.h"



TEST_GROUP(AdcWiring)
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



//*******************//
//*** Unit Tests! ***//
//*******************//
TEST(AdcWiring, RegistersZeroAfterInit)
{
  LONGS_EQUAL(0, ADCSR);
  LONGS_EQUAL(0, ADMUX);
  LONGS_EQUAL(0, ADCH);
  LONGS_EQUAL(0, ADCL);
}

TEST(AdcWiring, SelectReferenceVoltage)
{
  uint8_t expected = 0xff;
  ADMUX = 0xff;

  //ADC_AVCC = 0b00, so clear its bits
  CBI(expected, REFS1);
  CBI(expected, REFS0);

  AdcWiring_Private_SelectReferenceVoltage(ADC_AVCC);
  CHECK_TRUE(IFBITMASK(expected, ADMUX, 0xff));
}

TEST(AdcWiring, SelectResultAdjust)
{
  uint8_t expected = 0xff;
  ADMUX = 0xff;

  //ADC_RIGHT_ADJUST= 0b0, so clear its bit
  CBI(expected, ADLAR);

  AdcWiring_Private_SelectResultAdjust(ADC_RIGHT_ADJUST);
  CHECK_TRUE(IFBITMASK(expected, ADMUX, 0xff));
}

TEST(AdcWiring, SelectInputAndGain)
{
  uint8_t expected = 0xff;
  ADMUX = 0xff;

  //ADC_SINGLE_ENDED_ADC0 = 0b00000, so clear its bits
  CBI(expected, MUX4);
  CBI(expected, MUX3);
  CBI(expected, MUX2);
  CBI(expected, MUX1);
  CBI(expected, MUX0);

  AdcWiring_Private_SelectInputAndGain(ADC_SINGLE_ENDED_ADC0);
  CHECK_TRUE(IFBITMASK(expected, ADMUX, 0xff));
}

TEST(AdcWiring, SetPrescaleFactor)
{
  uint8_t expected = 0xff;
  ADCSR = 0xff;

  CBI(expected, ADPS2);
  CBI(expected, ADPS1);
  CBI(expected, ADPS0);

  AdcWiring_Private_SelectPrescaleFactor(ADC_PRESCALE_FACTOR_0);
  CHECK_TRUE(IFBITMASK(expected, ADCSR, 0xff));
}

TEST(AdcWiring, Init)
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

  AdcWiring_HwSetup();
  CHECK_TRUE(IFBITMASK(expected_ADMUX, ADMUX, 0xff));
  CHECK_TRUE(IFBITMASK(expected_ADCSR, ADCSR, 0x07));
}

TEST(AdcWiring, Enable)
{
  AdcWiring_Enable();
  CHECK_TRUE(IFBIT(ADCSR, ADEN));
}

TEST(AdcWiring, FirstConversion)
{
  AdcWiring_FirstConversion();
  CHECK_TRUE(IFBIT(ADCSR, ADSC));
}

TEST(AdcWiring, IsAdcBusy)
{
  CHECK_FALSE(AdcWiring_IsAdcBusy());
  SBI(ADCSR, ADSC);
  CHECK_TRUE(AdcWiring_IsAdcBusy());
}

TEST(AdcWiring, StartConversion)
{
  AdcWiring_StartConversion();
  CHECK_TRUE(IFBIT(ADCSR, ADSC));
}

TEST(AdcWiring, AdcWiring_IsInterruptFlagSet)
{
  CHECK_FALSE(AdcWiring_IsInterruptFlagSet());
  SBI(ADCSR, ADIF);
  CHECK_TRUE(AdcWiring_IsInterruptFlagSet());
}

TEST(AdcWiring, AdcWiring_ClearInterruptFlag)
{
  AdcWiring_ClearInterruptFlag();
  //Seems counterintuitive, but we write 1 to clear the flag. HW takes care of the rest.
  CHECK_TRUE(AdcWiring_IsInterruptFlagSet());
}

TEST(AdcWiring, ReadHighRegister_ReadZero)
{
  LONGS_EQUAL(0, AdcWiring_ReadDataRegister_High());
}

TEST(AdcWiring, ReadLowRegister_ReadZero)
{
  LONGS_EQUAL(0, AdcWiring_ReadDataRegister_Low());
}

TEST(AdcWiring, ReadHighRegister_ReadMax)
{
  ADCH = 0xff;
  LONGS_EQUAL(0b11, AdcWiring_ReadDataRegister_High());
}

TEST(AdcWiring, ReadLowRegister_ReadMax)
{
  ADCL = 0xff;
  LONGS_EQUAL(0xff, AdcWiring_ReadDataRegister_Low());
}
