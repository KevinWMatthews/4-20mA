extern "C"
{
  #include "AtoD.h" //Code under test
  #include "ADC.h"  //HW communication
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_AtoD.h"

TEST_GROUP(AtoD)
{
  int16_t adcReading;

  void setup()
  {
    adcReading = 0;
  }

  void teardown()
  {
    mock().clear();
  }
};


//*** Mock functions ***//
BOOL Adc_IsAdcBusy(void)
{
  mock().actualCall("Adc_IsAdcBusy");
  return (BOOL)(mock().intReturnValue());
}

void Adc_StartConversion(void)
{
  mock().actualCall("Adc_StartConversion");
  return;
}

BOOL Adc_IsInterruptFlagSet(void)
{
  mock().actualCall("Adc_IsInterruptFlagSet");
  return (BOOL)(mock().intReturnValue());
}

int16_t Adc_ReadDataRegisters(void)
{
  mock().actualCall("Adc_ReadDataRegisters");
  return mock().intReturnValue();
}

void Adc_ClearInterruptFlag(void)
{
  mock().actualCall("Adc_ClearInterruptFlag");
  return;
}

//*** The tests! ***//
TEST(AtoD, StartConversion_AdcIsBusy)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(TRUE);
  LONGS_EQUAL(ATOD_BUSY, AtoD_StartConversion());
  mock().checkExpectations();
}

TEST(AtoD, StartConversion_AdcIsFree)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_StartConversion");
  LONGS_EQUAL(ATOD_CONVERSION_STARTED, AtoD_StartConversion());
  mock().checkExpectations();
}

TEST(AtoD, Read_AdcIsBusy)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(TRUE);
  LONGS_EQUAL(ATOD_BUSY, AtoD_Read(&adcReading));
  mock().checkExpectations();
}

TEST(AtoD, Read_InterruptFlagNotSet)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_IsInterruptFlagSet")
        .andReturnValue(FALSE);
  LONGS_EQUAL(ATOD_INTERRUPT_FLAG_NOT_SET, AtoD_Read(&adcReading));
  mock().checkExpectations();
}

TEST(AtoD, Read_SuccessReadZero)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_IsInterruptFlagSet")
        .andReturnValue(TRUE);
  mock().expectOneCall("Adc_ReadDataRegisters");
  mock().expectOneCall("Adc_ClearInterruptFlag");
  LONGS_EQUAL(ATOD_READ_SUCCESS, AtoD_Read(&adcReading));
  LONGS_EQUAL(0, adcReading);
  mock().checkExpectations();
}

TEST(AtoD, Read_SuccessReadMax)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_IsInterruptFlagSet")
        .andReturnValue(TRUE);
  mock().expectOneCall("Adc_ReadDataRegisters")
        .andReturnValue(1023);
  mock().expectOneCall("Adc_ClearInterruptFlag");
  LONGS_EQUAL(ATOD_READ_SUCCESS, AtoD_Read(&adcReading));
  LONGS_EQUAL(1023, adcReading);
  mock().checkExpectations();
}
