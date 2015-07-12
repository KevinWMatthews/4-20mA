extern "C"
{
  #include "TimeServiceWiring.h"
  #include "TimeServiceWiringHw.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_TimeServiceWiring.h"

TEST_GROUP(TimeServiceWiring)
{
  void setup()
  {
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

TEST(TimeServiceWiring, HwSetup)
{
  mock().expectOneCall("TimeServiceWiringHw_SetPrescaler")
        .withParameter("prescaleFactor", TS_PRESCALE_FACTOR_64);
  mock().expectOneCall("TimeServiceWiringHw_SetTimerCompare")
        .withParameter("timerCompareValue", 125);
  mock().expectOneCall("TimeServiceWiringHw_ClearTimerOnMatch")
        .withParameter("clearOnMatchFlag", TRUE);
  mock().expectOneCall("TimeServiceWiringHw_SetTimerCompareInterrupt")
        .withParameter("enableInterrupt", TRUE);
  TimeServiceWiring_HwSetup();
}
