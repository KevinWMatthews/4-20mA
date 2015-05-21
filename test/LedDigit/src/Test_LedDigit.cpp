extern "C"
{
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedDigit.h"

TEST_GROUP(LedDigit)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(LedDigit, WiringCheck)
{
  FAIL("Start here!");
}
