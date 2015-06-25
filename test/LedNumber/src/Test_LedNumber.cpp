extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "LedDigit.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_LedNumber.h"

#define NUMBER_OF_DIGITS 4

int8_t dummyDigits[4];


TEST_GROUP(LedNumber)
{
  LedNumber number;
  LedDigit digits[NUMBER_OF_DIGITS];

  void setup()
  {
    number = LedNumber_Create(NUMBER_OF_DIGITS);
    for (int i = 0; i < NUMBER_OF_DIGITS; i++)
    {
      digits[i] = LedDigit_Create();
      LedNumber_AddLedDigit(number, digits[i], (LedNumber_DigitPlace)i);
    }
  }

  void teardown()
  {
    LedNumber_Destroy(&number);
    mock().checkExpectations();
    mock().clear();
  }

  void expectSetSingleDigit(LedDigit digit, int8_t value)
  {
    mock().expectOneCall("LedDigit_SetDigit")
          .withParameter("self", digit)
          .withParameter("value", value);
  }

  void expectSetDigits(int8_t led4, int8_t led3, int8_t led2, int8_t led1  )
  {
    expectSetSingleDigit(digits[0], led1);
    expectSetSingleDigit(digits[1], led2);
    expectSetSingleDigit(digits[2], led3);
    expectSetSingleDigit(digits[3], led4);
  }

  void expectClearSingleDigit(LedNumber_DigitPlace place)
  {
    mock().expectOneCall("LedDigit_ClearDigit")
          .withParameter("self", digits[place]);
  }

  void expectClearDigits(void)
  {
    expectClearSingleDigit(LED_1);
    expectClearSingleDigit(LED_2);
    expectClearSingleDigit(LED_3);
    expectClearSingleDigit(LED_4);
  }

  void expectShowDigit(LedDigit digit)
  {
    mock().expectOneCall("LedDigit_UpdateLed")
          .withParameter("self", digit);
  }

  void expectTurnOffDigit(LedDigit digit)
  {
    mock().expectOneCall("LedDigit_TurnLedOff")
          .withParameter("self", digit);
  }

  // void singleDigitShows(LedNumber self, int16_t numberToShow, int8_t numberOfDigits)
  // {
  //   LedNumber_SetNumber(self, numberToShow);
  //   LedNumber_ShowNumber(self);

  //   for (int i = 0; i < numberOfDigits; i++)
  //   {
  //     if (i == 0)
  //     {
  //       LONGS_EQUAL(PIN_ON, Spy_LedDigit_SelectPinState(spyDigits[numberOfDigits-1-i]));
  //     }
  //     else
  //     {
  //       LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[numberOfDigits-1-i]));
  //     }
  //   }
  // }

  // void allDigitsShowSequentially(LedNumber self, int16_t numberToShow, int8_t numberOfDigits)
  // {
  //   LedNumber_SetNumber(self, numberToShow);

  //   for (int i = 0; i < numberOfDigits; i++)
  //   {
  //     LedNumber_ShowNumber(self);
  //     for (int j = 0; j < numberOfDigits; j++)
  //     {
  //       if (j == i)
  //       {
  //         LONGS_EQUAL(PIN_ON, Spy_LedDigit_SelectPinState(spyDigits[numberOfDigits-1-j]));
  //       }
  //       else
  //       {
  //         LONGS_EQUAL(PIN_OFF, Spy_LedDigit_SelectPinState(spyDigits[numberOfDigits-1-j]));
  //       }
  //     }
  //   }
  // }
};

//**********************//
//*** Mock Functions ***//
//**********************//
LedDigit LedDigit_Create(void)
{
  static int i = 0;
  return (LedDigit)&dummyDigits[i++]; //It really is dumb, but it prevents null checks pointer from failing
}

void LedDigit_Destroy(LedDigit * self)
{}

void LedDigit_SetDigit(LedDigit self, LedDigit_DisplayDigit value)
{
  mock().actualCall("LedDigit_SetDigit")
        .withParameter("self", self)
        .withParameter("value", value);
}

void LedDigit_ClearDigit(LedDigit self)
{
  mock().actualCall("LedDigit_ClearDigit")
        .withParameter("self", self);
}

// void LedDigit_ClearDecimal(LedDigit self);
// void LedDigit_ClearAll(LedDigit self);
// LedDigit_DisplayDigit LedDigit_CurrentDigit(LedDigit self);
// BOOL LedDigit_IsDecimalShown(LedDigit self);

void LedDigit_UpdateLed(LedDigit self)
{
    mock().actualCall("LedDigit_UpdateLed")
          .withParameter("self", self);
}

void LedDigit_TurnLedOff(LedDigit self)
{
  mock().actualCall("LedDigit_TurnLedOff")
        .withParameter("self", self);
}



//*******************//
//*** Unit Tests  ***//
//*******************//
TEST(LedNumber, Create)
{
}

TEST(LedNumber, DestroyCanHandleNullNumber)
{
  LedNumber_Destroy(NULL);
}

TEST(LedNumber, AllFunctionsCanHandleNull)
{
  LedNumber_AddLedDigit(NULL, digits[0], LED_1);
  LedNumber_SetNumber(NULL, 1234);
  LedNumber_ClearNumber(NULL);
  LedNumber_ShowNumber(NULL);
  LedNumber_TurnOff(NULL);
}

TEST(LedNumber, SetSingleDigitNumber)
{
  expectSetDigits(0, 0, 0, 7);
  LedNumber_SetNumber(number, 7);
}

TEST(LedNumber, SetFourDigitNumber)
{
  expectSetDigits(6, 7, 8, 9);
  LedNumber_SetNumber(number, 6789);
}

TEST(LedNumber, ClearNumber)
{
  expectSetDigits(2, 3, 4, 5);
  LedNumber_SetNumber(number, 2345);

  expectClearDigits();
  LedNumber_ClearNumber(number);
}

TEST(LedNumber, ShowNumber)
{
  expectSetDigits(4, 5, 6, 7);
  LedNumber_SetNumber(number, 4567);


  expectShowDigit(digits[LED_MAX-1]);
  LedNumber_ShowNumber(number);

  for (int i = LED_MAX-1; i > LED_NONE+1; i--)
  {
    expectTurnOffDigit(digits[i]);
    expectShowDigit(digits[i-1]);
    LedNumber_ShowNumber(number);
  }

  expectTurnOffDigit(digits[0]);
  expectShowDigit(digits[LED_MAX-1]);
  LedNumber_ShowNumber(number);
}

TEST(LedNumber, TurnOffLedNumber)
{
  expectSetDigits(4, 5, 6, 7);
  LedNumber_SetNumber(number, 4567);

  expectShowDigit(digits[LED_MAX-1]);
  LedNumber_ShowNumber(number);

  expectTurnOffDigit(digits[LED_MAX-1]);
  LedNumber_TurnOff(number);

  expectShowDigit(digits[LED_MAX-1]);
  LedNumber_ShowNumber(number);
}
