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

#define NUMBER_OF_DIGITS 4

TEST_GROUP(LedNumber)
{
  LedDigit_DataPins dataPins;
  LedNumber number;

  Spy_LedDigit spyDigits[NUMBER_OF_DIGITS]; //An array of pointers
  Pin ledSelectPins[NUMBER_OF_DIGITS];

  void setup()
  {
    number = LedNumber_Create(NUMBER_OF_DIGITS);
    for (int i = 0; i < NUMBER_OF_DIGITS; i++)
    {
      spyDigits[i] = (Spy_LedDigit)LedDigit_Create(&dataPins);
      //Watch out for changes to the DigitPlace enum
      LedNumber_AddLedDigit(number, (LedDigit)spyDigits[i], (LedNumber_DigitPlace)i, &ledSelectPins[i]);
    }
  }

  void teardown()
  {
    LedNumber_Destroy(&number);
  }

  LedDigit_DisplayDigit getSpyDigit(LedNumber_DigitPlace place)
  {
    return *spyDigits[place];
  }

  Pin getLedSelectPinState(LedNumber_DigitPlace place)
  {
    return ledSelectPins[place];
  }
};

TEST(LedNumber, Create)
{
  //TODO learn how to detect a memory leak!
  for (int i = 0; i < NUMBER_OF_DIGITS; i++)
  {
    LONGS_EQUAL(NOTHING, getSpyDigit((LedNumber_DigitPlace)i));
    LONGS_EQUAL(PIN_OFF, getLedSelectPinState((LedNumber_DigitPlace)i));
  }
}

TEST(LedNumber, DestroyCanHandleNullNumber)
{
  LedNumber_Destroy(NULL);
}

TEST(LedNumber, AllFunctionsCanHandleNullDigits)
{
  LedDigit_DataPins dataPins;
  LedNumber hasNullDigits = LedNumber_Create(4);
  LedNumber_AddLedDigit(hasNullDigits, NULL, LED1, &ledSelectPins[LED1]);
  LedNumber_AddLedDigit(hasNullDigits, NULL, LED2, &ledSelectPins[LED2]);
  LedNumber_AddLedDigit(hasNullDigits, NULL, LED3, &ledSelectPins[LED3]);
  LedNumber_AddLedDigit(hasNullDigits, NULL, LED4, &ledSelectPins[LED4]);

  LedNumber_Show(hasNullDigits, 5);

  LedNumber_Destroy(&hasNullDigits);
}

// TEST(LedNumber, ShowNothingIfLedDigitsNotSet)

TEST(LedNumber, ShowSingleDigitNumber)
{
  LedNumber_Show(number, 7);
  LONGS_EQUAL(SEVEN, getSpyDigit(LED1));
  LONGS_EQUAL(PIN_ON, getLedSelectPinState(LED1));
}

TEST(LedNumber, ShowFourDigitNumber)
{
  LedNumber_Show(number, 6789);
  LONGS_EQUAL(SIX, getSpyDigit(LED4));
  LONGS_EQUAL(SEVEN, getSpyDigit(LED3));
  LONGS_EQUAL(EIGHT, getSpyDigit(LED2));
  LONGS_EQUAL(NINE, getSpyDigit(LED1));
  LONGS_EQUAL(PIN_ON, getLedSelectPinState(LED4));
  LONGS_EQUAL(PIN_ON, getLedSelectPinState(LED3));
  LONGS_EQUAL(PIN_ON, getLedSelectPinState(LED2));
  LONGS_EQUAL(PIN_ON, getLedSelectPinState(LED1));
}
