extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "Spy_LedDigit.h"
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
    Spy_LedDigit_Create(NUMBER_OF_DIGITS);
    LedNumber_Create(NUMBER_OF_DIGITS);
  }

  void teardown()
  {
    Spy_LedDigit_Destroy();
    LedNumber_Destroy();
  }
};

TEST(LedNumber, CreateAndDestroy)
{
  //TODO learn how to detect a memory leak!
}

TEST(LedNumber, ShowDigitOnFirstLed)
{
  LedNumber_ShowNumber(7);
  LONGS_EQUAL(SEVEN, LedDigitSpy_GetDigit(1));
}

TEST(LedNumber, ShowDigitOnTwoLeds)
{
  LedNumber_ShowNumber(67);
  LONGS_EQUAL(SEVEN, LedDigitSpy_GetDigit(1));
  LONGS_EQUAL(SIX, LedDigitSpy_GetDigit(2));
}

TEST(LedNumber, ShowDigitOnThreeLeds)
{
  LedNumber_ShowNumber(234);
  LONGS_EQUAL(FOUR, LedDigitSpy_GetDigit(1));
  LONGS_EQUAL(THREE, LedDigitSpy_GetDigit(2));
  LONGS_EQUAL(TWO, LedDigitSpy_GetDigit(3));
}
