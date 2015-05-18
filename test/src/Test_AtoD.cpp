extern "C"
{
  #include "AtoD.h" //Code under test
  #include "ADC.h"  //HW communication
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_AtoD.h"

static uint8_t adcsr; //ADC Control and Status Register

TEST_GROUP(AtoD)
{
  int16_t adcReading;

  void setup()
  {
    adcsr = 0;
    adcReading = 0;
  }

  void teardown()
  {
    mock().clear();
  }
};


//*** Mock functions ***//
//Helper functions
BOOL checkRegister(uint8_t adcRegister, uint8_t bitmask)
{
  return (BOOL)(1 && (adcRegister & bitmask));
}

void setAdcBusy(void)
{
  adcsr |= ADSC;
}

void setInterruptFlag(void)
{
  adcsr |= ADIF;
}

void clearInterruptFlag(void)
{
  adcsr &= ~ADIF;
}

BOOL Adc_IsAdcBusy(void)
{
  mock().actualCall("Adc_IsAdcBusy");
  return checkRegister(adcsr, ADSC);
}

void Adc_StartConversion(void)
{
  mock().actualCall("Adc_StartConversion");
  setAdcBusy();
  return;
}

BOOL Adc_IsInterruptFlagSet(void)
{
  mock().actualCall("Adc_IsInterruptFlagSet");
  return checkRegister(adcsr, ADIF);
}

int16_t Adc_ReadDataRegisters(void)
{
  mock().actualCall("Adc_ReadDataRegisters");
  return mock().intReturnValue();
}

void Adc_ClearInterruptFlag(void)
{
  mock().actualCall("Adc_ClearInterruptFlag");
  clearInterruptFlag();
  return;
}

//*** The tests! ***//
TEST(AtoD, StartConversion_AdcIsBusy)
{
  setAdcBusy();
  mock().expectOneCall("Adc_IsAdcBusy");
  LONGS_EQUAL(ATOD_BUSY, AtoD_StartConversion());
  mock().checkExpectations();
}

TEST(AtoD, StartConversion_AdcIsFree)
{
  mock().expectOneCall("Adc_IsAdcBusy");
  mock().expectOneCall("Adc_StartConversion");
  LONGS_EQUAL(ATOD_CONVERSION_STARTED, AtoD_StartConversion());
  mock().checkExpectations();
}

TEST(AtoD, Read_AdcIsBusy)
{
  setAdcBusy();
  mock().expectOneCall("Adc_IsAdcBusy");
  LONGS_EQUAL(ATOD_BUSY, AtoD_Read(&adcReading));
  mock().checkExpectations();
}

TEST(AtoD, Read_InterruptFlagNotSet)
{
  clearInterruptFlag();
  mock().expectOneCall("Adc_IsAdcBusy");
  mock().expectOneCall("Adc_IsInterruptFlagSet");
  LONGS_EQUAL(ATOD_INTERRUPT_FLAG_NOT_SET, AtoD_Read(&adcReading));
  mock().checkExpectations();
}

TEST(AtoD, Read_SuccessReadZero)
{
  setInterruptFlag();
  mock().expectOneCall("Adc_IsAdcBusy");
  mock().expectOneCall("Adc_IsInterruptFlagSet");
  mock().expectOneCall("Adc_ReadDataRegisters");
  mock().expectOneCall("Adc_ClearInterruptFlag");
  LONGS_EQUAL(ATOD_READ_SUCCESS, AtoD_Read(&adcReading));
  LONGS_EQUAL(0, adcsr & ADIF)
  LONGS_EQUAL(0, adcReading);
  mock().checkExpectations();
}

TEST(AtoD, Read_SuccessReadMax)
{
  setInterruptFlag();
  mock().expectOneCall("Adc_IsAdcBusy");
  mock().expectOneCall("Adc_IsInterruptFlagSet");
  mock().expectOneCall("Adc_ReadDataRegisters")
        .andReturnValue(1023);
  mock().expectOneCall("Adc_ClearInterruptFlag");
  LONGS_EQUAL(ATOD_READ_SUCCESS, AtoD_Read(&adcReading));
  LONGS_EQUAL(0, adcsr & ADIF)
  LONGS_EQUAL(1023, adcReading);
  mock().checkExpectations();
}
