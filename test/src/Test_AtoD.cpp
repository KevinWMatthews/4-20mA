extern "C"
{
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_AtoD.h"

TEST_GROUP(AtoD)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(AtoD, WiringCheck)
{
  FAIL("Start here!");
}
