extern "C"
{
  #include "Adc.h"  //Code under test
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_Adc.h"

TEST_GROUP(Adc)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(Adc, WiringCheck)
{
  FAIL("Start here!");
}
