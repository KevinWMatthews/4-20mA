extern "C"
{
  #include "TimeServiceWiring.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_TimeServiceWiring.h"

TEST_GROUP(TimeServiceWiring)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(TimeServiceWiring, WiringCheck)
{
  FAIL("Start here!");
}
