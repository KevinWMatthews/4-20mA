extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "Spy_LedDigit.h"
  #include "DataTypes.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedNumber.h"


TEST_GROUP(LedNumber)
{
  void setup()
  {
    LedNumber_Create(1);
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

TEST(LedNumber, ShowDigitOnFirstLed)
{
  LedNumber_ShowNumber(1, 7);
  LONGS_EQUAL(SEVEN, LedDigitSpy_GetDigit(1));
}

