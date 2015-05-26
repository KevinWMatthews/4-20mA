extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "DataTypes.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedNumber.h"

#define NUMBER_OF_DIGITS 3

TEST_GROUP(LedNumber)
{
  void setup()
  {
    LedNumber_Create(NUMBER_OF_DIGITS);
  }

  void teardown()
  {
    LedNumber_Destroy();
  }
};

TEST(LedNumber, CreateAndDestroy)
{
  //TODO learn how to detect a memory leak!
}
