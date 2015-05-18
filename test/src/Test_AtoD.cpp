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

void setAdcAsBusy(void)
{
  adcsr |= ADSC;
}

BOOL isAdcBusy(void)
{
  mock().actualCall("isAdcBusy");
  return checkRegister(adcsr, ADSC);
}

void startConversion(void)
{
  mock().actualCall("startConversion");
  setAdcAsBusy();
  return;
}

BOOL isInterruptFlagSet(void)
{
  mock().actualCall("isInterruptFlagSet");
  return checkRegister(adcsr, ADIF);
}


//*** The tests! ***//
TEST(AtoD, StartConversion_AdcIsBusy)
{
  setAdcAsBusy();
  mock().expectOneCall("isAdcBusy");
  LONGS_EQUAL(ATOD_BUSY, AtoD_StartConversion());
  mock().checkExpectations();
}

TEST(AtoD, StartConversion_AdcIsFree)
{
  mock().expectOneCall("isAdcBusy");
  mock().expectOneCall("startConversion");
  LONGS_EQUAL(ATOD_CONVERSION_STARTED, AtoD_StartConversion());
  mock().checkExpectations();
}

TEST(AtoD, Read_AdcIsBusy)
{
  setAdcAsBusy();
  mock().expectOneCall("isAdcBusy");
  LONGS_EQUAL(ATOD_BUSY, AtoD_Read(&adcReading));
  mock().checkExpectations();
}
