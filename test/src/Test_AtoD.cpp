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
BOOL isAdcBusy(void)
{
  mock().actualCall("isAdcBusy");
  return (BOOL)(1 && (adcsr & ADSC));
}

//*** The tests! ***//
TEST(AtoD, AdcIsBusy)
{
  adcsr |= ADSC;
  mock().expectOneCall("isAdcBusy");
  LONGS_EQUAL(ATOD_BUSY, AtoD_Read());
  mock().checkExpectations();
}
