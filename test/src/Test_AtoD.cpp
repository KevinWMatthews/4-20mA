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
  void setup()
  {
    adcsr = 0;
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

BOOL isAdcBusy(void)
{
  mock().actualCall("isAdcBusy");
  return checkRegister(adcsr, ADSC);
}

void startConversion(void)
{
  mock().actualCall("startConversion");
  adcsr |= ADSC;
  return;
}

BOOL isInterruptFlagSet(void)
{
  mock().actualCall("isInterruptFlagSet");
  return checkRegister(adcsr, ADIF);
}


//*** The tests! ***//
TEST(AtoD, AdcIsBusy)
{
  adcsr |= ADSC;
  mock().expectOneCall("isAdcBusy");
  LONGS_EQUAL(ATOD_BUSY, AtoD_Read());
  mock().checkExpectations();
}

TEST(AtoD, StartConversion)
{
  mock().expectOneCall("isAdcBusy");
  mock().expectOneCall("startConversion");
  mock().expectOneCall("isInterruptFlagSet");
  LONGS_EQUAL(ATOD_BUSY, AtoD_Read());
  mock().checkExpectations();
}
