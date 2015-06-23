extern "C"
{
  #include "DataTypes.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_DataTypes.h"

TEST_GROUP(DataTypes)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(DataTypes, WiringCheck)
{
  FAIL("Start here!");
}
