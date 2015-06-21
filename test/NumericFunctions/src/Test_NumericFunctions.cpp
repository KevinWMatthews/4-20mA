extern "C"
{
  #include "NumericFunctions.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_NumericFunctions.h"

TEST_GROUP(NumericFunctions)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(NumericFunctions, WiringCheck)
{
  FAIL("Start here!");
}
