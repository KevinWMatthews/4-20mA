extern "C"
{
  #include "LineFit.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_LineFit.h"

TEST_GROUP(LineFit)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(LineFit, WiringCheck)
{
  FAIL("Start here!");
}
