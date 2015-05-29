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
  LedNumber number;
  Spy_LedDigit spyDigits[NUMBER_OF_DIGITS]; //An array of pointers
  LedDigit_DataPins dummyDataPins;          //Used just to make LedDigit_Create() happy
  Pin dummySelectPins[NUMBER_OF_DIGITS];

  void setup()
  {
    number = LedNumber_Create(NUMBER_OF_DIGITS);
    for (int i = 0; i < NUMBER_OF_DIGITS; i++)
    {
      spyDigits[i] = (Spy_LedDigit)LedDigit_Create(&dummyDataPins, &dummySelectPins[i]);
      //Watch out for changes to the DigitPlace enum
      LedNumber_AddLedDigit(number, (LedDigit)spyDigits[i], (LedNumber_DigitPlace)i);
    }
  }

  void teardown()
  {
    LedNumber_Destroy(&number);
  }

  void singleDigitShows(LedNumber self, int16_t numberToShow, int8_t numberOfDigits)
  {
    LedNumber_SetNumber(self, numberToShow);
    LedNumber_ShowNumber(self);

    for (int i = 0; i < numberOfDigits; i++)
    {
      if (i == 0)
      {
        LONGS_EQUAL(PIN_ON, Spy_LedDigit_SelectPinState(spyDigits[numberOfDigits-1-i]));
      }
      else
      {
        LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[numberOfDigits-1-i]));
      }
    }
  }

  void allDigitsShowSequentially(LedNumber self, int16_t numberToShow, int8_t numberOfDigits)
  {
    LedNumber_SetNumber(self, numberToShow);

    for (int i = 0; i < numberOfDigits; i++)
    {
      LedNumber_ShowNumber(self);
      for (int j = 0; j < numberOfDigits; j++)
      {
        if (j == i)
        {
          LONGS_EQUAL(PIN_ON, Spy_LedDigit_SelectPinState(spyDigits[numberOfDigits-1-j]));
        }
        else
        {
          LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[numberOfDigits-1-j]));
        }
      }
    }
  }
};

//*** Test initialization and response to NULL pointers ***//
TEST(LedNumber, Create)
{
  //TODO learn how to detect a memory leak!
  for (int i = 0; i < NUMBER_OF_DIGITS; i++)
  {
    LONGS_EQUAL(NOTHING, Spy_LedDigit_CurrentDigit(spyDigits[i]));
    LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[i]));
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
  LedNumber_AddLedDigit(hasNullDigits, NULL, LED1);
  LedNumber_AddLedDigit(hasNullDigits, NULL, LED2);
  LedNumber_AddLedDigit(hasNullDigits, NULL, LED3);
  LedNumber_AddLedDigit(hasNullDigits, NULL, LED4);

  LedNumber_SetNumber(hasNullDigits, 5);

  LedNumber_Destroy(&hasNullDigits);
}


//*** Test functionality ***//
TEST(LedNumber, SetSingleDigitNumber)
{
  LedNumber_SetNumber(number, 7);

  LONGS_EQUAL(SEVEN, Spy_LedDigit_CurrentDigit(spyDigits[LED1]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED1]));
}

TEST(LedNumber, SetFourDigitNumber)
{
  LedNumber_SetNumber(number, 6789);

  LONGS_EQUAL(SIX, Spy_LedDigit_CurrentDigit(spyDigits[LED4]));
  LONGS_EQUAL(SEVEN, Spy_LedDigit_CurrentDigit(spyDigits[LED3]));
  LONGS_EQUAL(EIGHT, Spy_LedDigit_CurrentDigit(spyDigits[LED2]));
  LONGS_EQUAL(NINE, Spy_LedDigit_CurrentDigit(spyDigits[LED1]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED4]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED3]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED2]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED1]));
}

TEST(LedNumber, ClearNumber)
{
  LedNumber_SetNumber(number, 2345);
  LedNumber_ClearNumber(number);

  LONGS_EQUAL(NOTHING, Spy_LedDigit_CurrentDigit(spyDigits[LED4]));
  LONGS_EQUAL(NOTHING, Spy_LedDigit_CurrentDigit(spyDigits[LED3]));
  LONGS_EQUAL(NOTHING, Spy_LedDigit_CurrentDigit(spyDigits[LED2]));
  LONGS_EQUAL(NOTHING, Spy_LedDigit_CurrentDigit(spyDigits[LED1]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED4]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED3]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED2]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED1]));
}

TEST(LedNumber, ShowFourDigitsWithFourInitialized)
{
  allDigitsShowSequentially(number, 2345, NUMBER_OF_DIGITS);
  singleDigitShows(number, 2345, NUMBER_OF_DIGITS);
}

TEST(LedNumber, ShowThreeDigitsWithFourInitialized)
{
  allDigitsShowSequentially(number, 987, NUMBER_OF_DIGITS);
  singleDigitShows(number, 987, NUMBER_OF_DIGITS);
}

TEST(LedNumber, ShowOneDigitWithFourInitialized)
{
  allDigitsShowSequentially(number, 0, NUMBER_OF_DIGITS);
  singleDigitShows(number, 0, NUMBER_OF_DIGITS);
}

TEST(LedNumber, TurnOffLedNumber)
{
  LedNumber_SetNumber(number, 4567);
  LedNumber_ShowNumber(number);
  LedNumber_TurnOff(number);

  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED4]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED3]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED2]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED1]));

  LedNumber_ShowNumber(number);

  LONGS_EQUAL(PIN_ON, Spy_LedDigit_SelectPinState(spyDigits[LED4]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED3]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED2]));
  LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[LED1]));
}
