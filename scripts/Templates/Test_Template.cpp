extern "C"
{
  #include "<Name>.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_<Name>.h"

TEST_GROUP(<Name>)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(<Name>, WiringCheck)
{
  FAIL("Start here!");
}
