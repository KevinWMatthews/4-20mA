extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "Spy_LedDigit.h"
  #include "DataTypes.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedNumber.h"

#define NUMBER_OF_DIGITS 2

//Simulate memory address of select pin
static Pin ledSelect[NUMBER_OF_DIGITS];

TEST_GROUP(LedNumber)
{
  void setup()
  {
    for (int i = 0; i < NUMBER_OF_DIGITS; i++)
    {
      ledSelect[i] = PIN_UNDEFINED;
    }
    LedNumber_Create(NUMBER_OF_DIGITS);
    for (int i = 0; i < NUMBER_OF_DIGITS; i++)
    {
      LedNumber_WireSelectPin(i+1, &ledSelect[i]); //TODO macro
    }
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

TEST(LedNumber, SelectPinsUndefinedAfterCreate)
{
  for (int i = 0; i < NUMBER_OF_DIGITS; i++)
  {
    LONGS_EQUAL(ledSelect[i], PIN_UNDEFINED);
  }
}

TEST(LedNumber, ShowDigitOnFirstLed)
{
  LedNumber_ShowNumber(1, 7);
  LONGS_EQUAL(PIN_ON, ledSelect[0]);
  LONGS_EQUAL(SEVEN, LedDigitSpy_GetDigit());
}

TEST(LedNumber, ShowDigitOnSecondLed)
{

}
