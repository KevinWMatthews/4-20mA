extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "DataTypes.h"
  #include "Spy_LedDigit.h"
  #include <string.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedNumber.h"

#define NUMBER_OF_DIGITS 1


TEST_GROUP(LedNumber)
{
  LedDigit_DataPins dataPins;
  LedNumber number;
  Spy_LedDigit spy_led1;
  Pin selectPinLed1;

  void setup()
  {
    // Spy_LedDigit_Create(NUMBER_OF_DIGITS);
    number = LedNumber_Create(NUMBER_OF_DIGITS);
    spy_led1 = (Spy_LedDigit)LedDigit_Create(&dataPins);
    LedNumber_AddLedDigit(number, (LedDigit)spy_led1, LED1, &selectPinLed1);
  }

  void teardown()
  {
    // Spy_LedDigit_Destroy();
    LedNumber_Destroy(&number);
  }
};

TEST(LedNumber, Create)
{
  //TODO learn how to detect a memory leak!
  LONGS_EQUAL(NOTHING, *spy_led1);
  LONGS_EQUAL(PIN_OFF, selectPinLed1);
}

TEST(LedNumber, Destroy)
{
}

TEST(LedNumber, ShowSingleDigitNumber)
{
  LedNumber_Show(number, 7);
  LONGS_EQUAL(SEVEN, *spy_led1);
  LONGS_EQUAL(PIN_ON, selectPinLed1);
}
