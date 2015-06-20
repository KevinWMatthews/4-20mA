extern "C"
{
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_MainLoop.h"

TEST_GROUP(MainLoop)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(MainLoop, WiringCheck)
{
  FAIL("Start here!");
}
