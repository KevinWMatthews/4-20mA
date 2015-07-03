extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "LedDigit.h"
  #include "LedNumberWiring.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_LedNumber.h"

#define NUMBER_OF_DIGITS 4
#define MAX_TWO 2

int8_t dummyDigit;  // To prevent null checks from failing


TEST_GROUP(LedNumber)
{
  LedNumber number;
  LedNumber twoDigitNumber;
  LedDigit digits[NUMBER_OF_DIGITS];
  LedDigit twoDigits[MAX_TWO];

  void setup()
  {
    number = LedNumber_Create(NUMBER_OF_DIGITS);
    for (int i = 0; i < NUMBER_OF_DIGITS; i++)
    {
      digits[i] = LedDigit_Create();
      LedNumber_AddLedDigit(number, digits[i], (LedNumber_DigitPlace)i);
    }

    twoDigitNumber = LedNumber_Create(MAX_TWO);
    for (int i = 0; i < MAX_TWO; i++)
    {
      twoDigits[i] = LedDigit_Create();
      LedNumber_AddLedDigit(twoDigitNumber, twoDigits[i], (LedNumber_DigitPlace)i);
    }
  }

  void teardown()
  {
    LedNumber_Destroy(&number);
    LedNumber_Destroy(&twoDigitNumber);
    mock().checkExpectations();
    mock().clear();
  }

  void expectSetSingleDigit(LedDigit digit, int8_t value)
  {
    mock().expectOneCall("LedDigit_SetDigit")
          .withParameter("self", digit)
          .withParameter("value", value);
  }

  void expectSetTwoDigits(int8_t led1, int8_t led2)
  {
    expectSetSingleDigit(digits[0], led1);
    expectSetSingleDigit(digits[1], led2);
  }

  void expectSetDigits(int8_t led4, int8_t led3, int8_t led2, int8_t led1 )
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

  void expectClearTwoDigits(void)
  {
    expectClearSingleDigit(LED_1);
    expectClearSingleDigit(LED_2);
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

  void expectSetSelectPin(LedNumber_DigitPlace led_number)
  {
    mock().expectOneCall("LedNumberWring_SetSelectPin")
          .withParameter("pin", led_number);
  }
};



//**********************//
//*** Mock Functions ***//
//**********************//
LedDigit LedDigit_Create(void)
{
  return (LedDigit)&dummyDigit;   //It it prevents null checks pointer from failing
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

void LedDigit_ClearDecimal(LedDigit self)
{
  mock().actualCall("LedDigit_ClearDecimal")
        .withParameter("self", self);
}

void LedDigit_ClearAll(LedDigit self)
{
  mock().actualCall("LedDigit_ClearAll")
        .withParameter("self", self);
}

LedDigit_DisplayDigit LedDigit_CurrentDigit(LedDigit self)
{
  mock().actualCall("LedDigit_CurrentDigit")
        .withParameter("self", self);
}

BOOL LedDigit_IsDecimalShown(LedDigit self)
{
  mock().actualCall("LedDigit_IsDecimalShown")
        .withParameter("self", self);
}


void LedNumberWiring_Init(void)
{
  mock().actualCall("LedNumberWiring_Init");
}

void LedNumberWring_SetSelectPin(LedNumber_DigitPlace pin)
{
  mock().actualCall("LedNumberWring_SetSelectPin")
        .withParameter("pin", pin);
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

  expectTurnOffDigit(digits[LED_MAX-1]);
  expectSetSelectPin((LedNumber_DigitPlace)(LED_MAX-1));
  expectShowDigit(digits[LED_MAX-1]);
  LedNumber_ShowNumber(number);

  for (int i = LED_MAX-1; i > LED_NONE+1; i--)
  {
    expectTurnOffDigit(digits[i]);
    expectSetSelectPin((LedNumber_DigitPlace)(i-1));
    expectShowDigit(digits[i-1]);
    LedNumber_ShowNumber(number);
  }

  expectTurnOffDigit(digits[LED_MAX-1]);
  expectSetSelectPin((LedNumber_DigitPlace)(LED_MAX-1));
  expectShowDigit(digits[LED_MAX-1]);
  LedNumber_ShowNumber(number);
}

TEST(LedNumber, TurnOffLedNumber)
{
  expectSetDigits(4, 5, 6, 7);
  LedNumber_SetNumber(number, 4567);

  expectTurnOffDigit(digits[LED_MAX-1]);
  expectSetSelectPin((LedNumber_DigitPlace)(LED_MAX-1));
  expectShowDigit(digits[LED_MAX-1]);
  LedNumber_ShowNumber(number);

  expectSetSelectPin(LED_NONE);
  LedNumber_TurnOff(number);

  expectTurnOffDigit(digits[LED_MAX-1]);
  expectSetSelectPin((LedNumber_DigitPlace)(LED_MAX-1));
  expectShowDigit(digits[LED_MAX-1]);
  LedNumber_ShowNumber(number);
}

//*** Two digit number ***//
TEST(LedNumber, Two_SetSingleDigitNumber)
{
  expectSetTwoDigits(0, 7);
  LedNumber_SetNumber(twoDigitNumber, 7);
}

TEST(LedNumber, Two_SetMaxDigitNumber)
{
  expectSetTwoDigits(8, 9);
  LedNumber_SetNumber(twoDigitNumber, 89);
}

TEST(LedNumber, Two_ClearNumber)
{
  expectSetTwoDigits(2, 3);
  LedNumber_SetNumber(twoDigitNumber, 23);

  expectClearTwoDigits();
  LedNumber_ClearNumber(twoDigitNumber);
}

TEST(LedNumber, Two_ShowNumber)
{
  expectSetTwoDigits(6, 7);
  LedNumber_SetNumber(twoDigitNumber, 67);

  expectTurnOffDigit(twoDigits[MAX_TWO-1]);
  expectShowDigit(twoDigits[MAX_TWO-1]);
  expectSetSelectPin((LedNumber_DigitPlace)(MAX_TWO-1));
  LedNumber_ShowNumber(twoDigitNumber);

  for (int i = MAX_TWO-1; i > LED_NONE+1; i--)
  {
    expectTurnOffDigit(twoDigits[i]);
    expectSetSelectPin((LedNumber_DigitPlace)(i-1));
    expectShowDigit(twoDigits[i-1]);
    LedNumber_ShowNumber(twoDigitNumber);
  }

  expectTurnOffDigit(twoDigits[0]);
  expectSetSelectPin((LedNumber_DigitPlace)(MAX_TWO-1));
  expectShowDigit(twoDigits[MAX_TWO-1]);
  LedNumber_ShowNumber(twoDigitNumber);
}

