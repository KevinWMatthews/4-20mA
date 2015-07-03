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


int8_t dummyDigit;  // To prevent null checks from failing


TEST_GROUP(LedNumber)
{
  LedNumber fourDigitNumber;
  LedDigit fourDigits[LED_UPPER_BOUND];

  void setup()
  {
    mock().strictOrder();
    fourDigitNumber = LedNumber_Create(LED_THOUSANDS);
    for (int i = 0; i <= LED_THOUSANDS; i++)
    {
      fourDigits[i] = LedDigit_Create();
      LedNumber_AddLedDigit(fourDigitNumber, fourDigits[i], (LedNumber_Place)i);
    }
  }

  void teardown()
  {
    LedNumber_Destroy(&fourDigitNumber);
    mock().checkExpectations();
    mock().clear();
  }

  void expectSetDigit(LedDigit digit, int8_t value)
  {
    mock().expectOneCall("LedDigit_SetDigit")
          .withParameter("self", digit)
          .withParameter("value", value);
  }

  void expectClearDigit(LedDigit digit)
  {
    mock().expectOneCall("LedDigit_ClearDigit")
          .withParameter("self", digit);
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

  void expectSetSelectPin(LedNumberWiring_Place led_number)
  {
    mock().expectOneCall("LedNumberWiring_SetSelectPin")
          .withParameter("pin", led_number);
  }

  void expectSetTwoDigits(int8_t led1, int8_t led2)
  {
    // expectSetDigit(digits[0], led1);
    // expectSetDigit(digits[1], led2);
  }

  void expectSetFourDigits(int8_t thousands, int8_t hundreds, int8_t tens, int8_t units)
  {
    expectSetDigit(fourDigits[3], units);
    expectSetDigit(fourDigits[2], tens);
    expectSetDigit(fourDigits[1], hundreds);
    expectSetDigit(fourDigits[0], thousands);
  }

  void expectClearTwoDigits(void)
  {
    // expectClearDigit(twoDigits[LED_UNITS]);
    // expectClearDigit(twoDigits[LED_TENS]);
  }

  void expectClearFourDigits(void)
  {
    expectClearDigit(fourDigits[LED_UNITS]);
    expectClearDigit(fourDigits[LED_TENS]);
    expectClearDigit(fourDigits[LED_HUNDREDS]);
    expectClearDigit(fourDigits[LED_THOUSANDS]);
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

void LedNumberWiring_SetSelectPin(LedNumberWiring_Place pin)
{
  mock().actualCall("LedNumberWiring_SetSelectPin")
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
  LONGS_EQUAL(LEDNUMBER_NULL_POINTER, LedNumber_AddLedDigit(NULL, fourDigits[0], LED_UNITS));
  LedNumber_SetNumber(NULL, 1234);
  LedNumber_ClearNumber(NULL);
  LedNumber_ShowNumber(NULL);
  LedNumber_TurnOff(NULL);
}

TEST(LedNumber, HardwareSetup)
{
  mock().expectOneCall("LedNumberWiring_Init");
  LedNumber_HwSetup();
}

TEST(LedNumber, AddFailsIfPlaceIsOutOfBounds)
{
  LONGS_EQUAL(LEDNUMBER_INVALID_PLACE, LedNumber_AddLedDigit(fourDigitNumber, fourDigits[0], LED_NONE));
  LONGS_EQUAL(LEDNUMBER_INVALID_PLACE, LedNumber_AddLedDigit(fourDigitNumber, fourDigits[0], LED_UPPER_BOUND));
}

TEST(LedNumber, AddFailsIfPlaceIsntSupported)
{
  // LONGS_EQUAL(LEDNUMBER_INVALID_PLACE, LedNumber_AddLedDigit(twoDigitNumber, twoDigits[0], LED_THOUSANDS));
}

TEST(LedNumber, GetUnitsDigitFromNumber)
{
  LONGS_EQUAL(1, getDigitFromNumber(4321, LED_UNITS));
}

TEST(LedNumber, GetTensDigitFromNumber)
{
  LONGS_EQUAL(2, getDigitFromNumber(4321, LED_TENS));
}

TEST(LedNumber, GetHundredsDigitFromNumber)
{
  LONGS_EQUAL(3, getDigitFromNumber(4321, LED_HUNDREDS));
}

TEST(LedNumber, GetThousandsDigitFromNumber)
{
  LONGS_EQUAL(4, getDigitFromNumber(4321, LED_THOUSANDS));
}

TEST(LedNumber, SetFourDigitNumber)
{
  expectSetFourDigits(6, 7, 8, 9);
  LedNumber_SetNumber(fourDigitNumber, 6789);
}

TEST(LedNumber, ClearFourDigitNumber)
{
  expectSetFourDigits(2, 3, 4, 5);
  LedNumber_SetNumber(fourDigitNumber, 2345);

  expectClearFourDigits();
  LedNumber_ClearNumber(fourDigitNumber);
}

TEST(LedNumber, ShowFourDigitNumber)
{
  expectSetFourDigits(4, 5, 6, 7);
  LedNumber_SetNumber(fourDigitNumber, 4567);

  expectTurnOffDigit(fourDigits[LED_UNITS]);
  expectSetSelectPin(WIRINGLED_UNITS);
  expectShowDigit(fourDigits[LED_UNITS]);
  LedNumber_ShowNumber(fourDigitNumber);

  expectTurnOffDigit(fourDigits[LED_TENS]);
  expectSetSelectPin(WIRINGLED_TENS);
  expectShowDigit(fourDigits[LED_TENS]);
  LedNumber_ShowNumber(fourDigitNumber);

  expectTurnOffDigit(fourDigits[LED_HUNDREDS]);
  expectSetSelectPin(WIRINGLED_HUNDREDS);
  expectShowDigit(fourDigits[LED_HUNDREDS]);
  LedNumber_ShowNumber(fourDigitNumber);

  expectTurnOffDigit(fourDigits[LED_THOUSANDS]);
  expectSetSelectPin(WIRINGLED_THOUSANDS);
  expectShowDigit(fourDigits[LED_THOUSANDS]);
  LedNumber_ShowNumber(fourDigitNumber);

  expectTurnOffDigit(fourDigits[LED_UNITS]);
  expectSetSelectPin(WIRINGLED_UNITS);
  expectShowDigit(fourDigits[LED_UNITS]);
  LedNumber_ShowNumber(fourDigitNumber);
}

TEST(LedNumber, TurnOffLedNumber)
{
  expectSetFourDigits(4, 5, 6, 7);
  LedNumber_SetNumber(fourDigitNumber, 4567);

  expectTurnOffDigit(fourDigits[LED_UNITS]);
  expectSetSelectPin(WIRINGLED_UNITS);
  expectShowDigit(fourDigits[LED_UNITS]);
  LedNumber_ShowNumber(fourDigitNumber);

  expectSetSelectPin(WIRINGLED_NONE);
  LedNumber_TurnOff(fourDigitNumber);

  expectTurnOffDigit(fourDigits[LED_UNITS]);
  expectSetSelectPin(WIRINGLED_UNITS);
  expectShowDigit(fourDigits[LED_UNITS]);
  LedNumber_ShowNumber(fourDigitNumber);
}

//*** Two digit number ***//
// TEST(LedNumber, Two_SetSingleDigitNumber)
// {
//   expectSetTwoDigits(0, 7);
//   LedNumber_SetNumber(twoDigitNumber, 7);
// }

// TEST(LedNumber, Two_SetMaxDigitNumber)
// {
//   expectSetTwoDigits(8, 9);
//   LedNumber_SetNumber(twoDigitNumber, 89);
// }

// TEST(LedNumber, Two_ClearNumber)
// {
//   expectSetTwoDigits(2, 3);
//   LedNumber_SetNumber(twoDigitNumber, 23);

//   expectClearTwoDigits();
//   LedNumber_ClearNumber(twoDigitNumber);
// }

// TEST(LedNumber, Two_ShowNumber)
// {
//   expectSetTwoDigits(6, 7);
//   LedNumber_SetNumber(twoDigitNumber, 67);

//   expectTurnOffDigit(twoDigits[0]);
//   expectShowDigit(twoDigits[LED_TENS-1]);
//   expectSetSelectPin((LedNumberWiring_Place)(0));
//   LedNumber_ShowNumber(twoDigitNumber);

//   for (int i = LED_TENS-1; i > LED_NONE+1; i--)
//   {
//     expectTurnOffDigit(twoDigits[i]);
//     expectSetSelectPin((LedNumberWiring_Place)(1));
//     expectShowDigit(twoDigits[i-1]);
//     LedNumber_ShowNumber(twoDigitNumber);
//   }

//   expectTurnOffDigit(twoDigits[0]);
//   expectSetSelectPin((LedNumberWiring_Place)(0));
//   expectShowDigit(twoDigits[LED_TENS-1]);
//   LedNumber_ShowNumber(twoDigitNumber);
// }

