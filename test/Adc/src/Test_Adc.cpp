extern "C"
{
  #include "Adc.h"  //Code under test
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_Adc.h"

uint8_t adcsr;

TEST_GROUP(Adc)
{
  void setup()
  {
    adcsr = 0;
    Adc_Init(&adcsr);
  }

  void teardown()
  {
  }
};

TEST(Adc, RegistersZeroAfterInit)
{
  LONGS_EQUAL(0, adcsr);
}

TEST(Adc, SelectReferenceVoltage)
{
  Adc_SelectReferenceVoltage(ADC_AVCC);
  LONGS_EQUAL(adcsr, ADC_AVCC);
}
