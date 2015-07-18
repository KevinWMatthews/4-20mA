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
  uint8_t expected;

  void setup()
  {
    ADCSR = 0;
    ADMUX = 0;
    ADCH = 0;
    ADCL = 0;
    expected = 0;
  }

  void teardown()
  {
  }
};



//*******************//
//*** Unit Tests! ***//
//*******************//
TEST(AdcWiring, RegistersZeroAfterSetup)
{
  LONGS_EQUAL(0, ADCSR);
  LONGS_EQUAL(0, ADMUX);
  LONGS_EQUAL(0, ADCH);
  LONGS_EQUAL(0, ADCL);
}

TEST(AdcWiring, SetAllReferenceVoltageBits)
{
  SET_BIT_NUMBER(expected, REFS1);
  SET_BIT_NUMBER(expected, REFS0);

  AdcWiring_Private_SelectReferenceVoltage(ADC_INTERNAL_WITH_AREF);
  CHECK_TRUE(IF_BITMASK(expected, ADMUX, 0xff));
}

TEST(AdcWiring, ClearAllReferenceVoltageBits)
{
  expected = 0xff;
  ADMUX = 0xff;

  CLEAR_BIT_NUMBER(expected, REFS1);
  CLEAR_BIT_NUMBER(expected, REFS0);

  AdcWiring_Private_SelectReferenceVoltage(ADC_AVCC);
  CHECK_TRUE(IF_BITMASK(expected, ADMUX, 0xff));
}

TEST(AdcWiring, SetAllResultAdjustBits)
{
  SET_BIT_NUMBER(expected, ADLAR);

  AdcWiring_Private_SelectResultAdjust(ADC_LEFT_ADJUST);
  CHECK_TRUE(IF_BITMASK(expected, ADMUX, 0xff));
}

TEST(AdcWiring, ClearAllResultAdjustBits)
{
  expected = 0xff;
  ADMUX = 0xff;

  CLEAR_BIT_NUMBER(expected, ADLAR);

  AdcWiring_Private_SelectResultAdjust(ADC_RIGHT_ADJUST);
  CHECK_TRUE(IF_BITMASK(expected, ADMUX, 0xff));
}

TEST(AdcWiring, SetAllInputAndGainBits)
{
  SET_BIT_NUMBER(expected, MUX4);
  SET_BIT_NUMBER(expected, MUX3);
  SET_BIT_NUMBER(expected, MUX2);
  SET_BIT_NUMBER(expected, MUX1);
  SET_BIT_NUMBER(expected, MUX0);

  AdcWiring_Private_SelectInputAndGain(ADC_GROUND);
  CHECK_TRUE(IF_BITMASK(expected, ADMUX, 0xff));
}

TEST(AdcWiring, ClearAllInputAndGainBits)
{
  expected = 0xff;
  ADMUX = 0xff;

  CLEAR_BIT_NUMBER(expected, MUX4);
  CLEAR_BIT_NUMBER(expected, MUX3);
  CLEAR_BIT_NUMBER(expected, MUX2);
  CLEAR_BIT_NUMBER(expected, MUX1);
  CLEAR_BIT_NUMBER(expected, MUX0);

  AdcWiring_Private_SelectInputAndGain(ADC_SINGLE_ENDED_ADC0);
  CHECK_TRUE(IF_BITMASK(expected, ADMUX, 0xff));
}

TEST(AdcWiring, SetAllPrescaleFactorBits)
{
  SET_BIT_NUMBER(expected, ADPS2);
  SET_BIT_NUMBER(expected, ADPS1);
  SET_BIT_NUMBER(expected, ADPS0);

  AdcWiring_Private_SelectPrescaleFactor(ADC_PRESCALE_FACTOR_128);
  BYTES_EQUAL(expected, ADCSR);
}

TEST(AdcWiring, ClearAllPrescaleFactorBits)
{
  expected = 0xff;
  ADCSR = 0xff;

  CLEAR_BIT_NUMBER(expected, ADPS2);
  CLEAR_BIT_NUMBER(expected, ADPS1);
  CLEAR_BIT_NUMBER(expected, ADPS0);

  AdcWiring_Private_SelectPrescaleFactor(ADC_PRESCALE_FACTOR_0);
  CHECK_TRUE(IF_BITMASK(expected, ADCSR, 0xff));
}

TEST(AdcWiring, Init)
{
  uint8_t expected_ADMUX = 0, expected_ADCSR = 0;

  //Expanded for ease of manipulation
  CLEAR_BIT_NUMBER(expected_ADMUX, REFS1);
  CLEAR_BIT_NUMBER(expected_ADMUX, REFS0);
  CLEAR_BIT_NUMBER(expected_ADMUX, ADLAR);
  CLEAR_BIT_NUMBER(expected_ADMUX, MUX4);
  CLEAR_BIT_NUMBER(expected_ADMUX, MUX3);
  CLEAR_BIT_NUMBER(expected_ADMUX, MUX2);
  CLEAR_BIT_NUMBER(expected_ADMUX, MUX1);
  CLEAR_BIT_NUMBER(expected_ADMUX, MUX0);
  CLEAR_BIT_NUMBER(expected_ADCSR, ADPS2);
  CLEAR_BIT_NUMBER(expected_ADCSR, ADPS1);
  SET_BIT_NUMBER(expected_ADCSR, ADPS0);

  AdcWiring_HwSetup();
  CHECK_TRUE(IF_BITMASK(expected_ADMUX, ADMUX, 0xff));
  CHECK_TRUE(IF_BITMASK(expected_ADCSR, ADCSR, 0x07));
}

TEST(AdcWiring, Enable)
{
  AdcWiring_Enable();
  CHECK_TRUE(IF_BIT_NUMBER(ADCSR, ADEN));
}

TEST(AdcWiring, FirstConversion)
{
  AdcWiring_FirstConversion();
  CHECK_TRUE(IF_BIT_NUMBER(ADCSR, ADSC));
}

TEST(AdcWiring, IsAdcBusy)
{
  CHECK_FALSE(AdcWiring_IsAdcBusy());
  SET_BIT_NUMBER(ADCSR, ADSC);
  CHECK_TRUE(AdcWiring_IsAdcBusy());
}

TEST(AdcWiring, StartConversion)
{
  AdcWiring_StartConversion();
  CHECK_TRUE(IF_BIT_NUMBER(ADCSR, ADSC));
}

TEST(AdcWiring, AdcWiring_IsInterruptFlagSet)
{
  CHECK_FALSE(AdcWiring_IsInterruptFlagSet());
  SET_BIT_NUMBER(ADCSR, ADIF);
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
