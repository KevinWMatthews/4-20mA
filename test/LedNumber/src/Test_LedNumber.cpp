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
static PinState led1Select;
static PinState led2Select;

TEST_GROUP(LedNumber)
{
  void setup()
  {
    led1Select = PIN_UNDEFINED;
    led2Select = PIN_UNDEFINED;
    LedNumber_Create(NUMBER_OF_DIGITS);
    LedNumber_WireSelectPin(1, &led1Select); //TODO macro
    LedNumber_WireSelectPin(2, &led2Select); //TODO macro
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
  LONGS_EQUAL(led1Select, PIN_UNDEFINED);
  LONGS_EQUAL(led2Select, PIN_UNDEFINED);
}

TEST(LedNumber, ShowDigitOnFirstLed)
{
  LedNumber_ShowNumber(1, 7);
  LONGS_EQUAL(PIN_ON, led1Select);
  LONGS_EQUAL(SEVEN, LedDigitSpy_GetDigit());
}

TEST(LedNumber, ShowDigitOnSecondLed)
{

}
