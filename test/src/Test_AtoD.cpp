extern "C"
{
  #include "AtoD.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_AtoD.h"

TEST_GROUP(AtoD)
{
  void setup()
  {
  }

  void teardown()
  {
    mock().clear();
  }
};

TEST(AtoD, WiringCheck)
{
  FAIL("Start here!");
}
