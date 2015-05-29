extern "C"
{
  #include "TimeService.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_TimeService.h"

TEST_GROUP(TimeService)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(TimeService, WiringCheck)
{
  FAIL("Start here!");
}
