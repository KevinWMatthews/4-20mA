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

  void setup()
  {
    mock().strictOrder();
    fourDigitNumber = LedNumber_Create(LED_THOUSANDS);
  }

  void teardown()
  {
    LedNumber_Destroy(&fourDigitNumber);
    mock().checkExpectations();
    mock().clear();
  }

  void expectSetDigit(LedDigit_DisplayDigit value)
  {
    mock().expectOneCall("LedDigit_SetDigit")
          .withParameter("self", &dummyDigit)
          .withParameter("value", value);
  }

  void expectShowDigit(void)
  {
    mock().expectOneCall("LedDigit_UpdateLed")
          .withParameter("self", &dummyDigit);
  }

  void expectTurnOffDigit(void)
  {
    mock().expectOneCall("LedDigit_TurnLedOff")
          .withParameter("self", &dummyDigit);
  }

  void expectSetSelectPin(LedNumberWiring_Place led_number)
  {
    mock().expectOneCall("LedNumberWiring_SetSelectPin")
          .withParameter("pin", led_number);
  }
};



//**********************//
//*** Mock Functions ***//
//**********************//
void LedDigit_HwSetup(void)
{
  mock().actualCall("LedDigit_HwSetup");
}

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


void LedNumberWiring_HwSetup(void)
{
  mock().actualCall("LedNumberWiring_HwSetup");
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
  LedNumber_SetNumber(NULL, 1234);
  // LedNumber_ClearNumber(NULL);
  // LedNumber_ShowNumber(NULL);
  // LedNumber_TurnOff(NULL);
}

TEST(LedNumber, HardwareSetup)
{
  mock().expectOneCall("LedDigit_HwSetup");
  mock().expectOneCall("LedNumberWiring_HwSetup");
  LedNumber_HwSetup();
}


TEST(LedNumber, GetUnitsDigitFromNumber)
{
  LONGS_EQUAL(1, LedDigitPrivate_GetDigitFromNumber(4321, LED_UNITS));
}

TEST(LedNumber, GetTensDigitFromNumber)
{
  LONGS_EQUAL(2, LedDigitPrivate_GetDigitFromNumber(4321, LED_TENS));
}

TEST(LedNumber, GetHundredsDigitFromNumber)
{
  LONGS_EQUAL(3, LedDigitPrivate_GetDigitFromNumber(4321, LED_HUNDREDS));
}

TEST(LedNumber, GetThousandsDigitFromNumber)
{
  LONGS_EQUAL(4, LedDigitPrivate_GetDigitFromNumber(4321, LED_THOUSANDS));
}

TEST(LedNumber, SetFourDigitNumber)
{
  LedNumber_SetNumber(fourDigitNumber, 6789);
  //Not sure what to test; nothing, really, unless we restructure things.
}

//Need to test with output/show
// TEST(LedNumber, ClearFourDigitNumber)
// {
//   LedNumber_SetNumber(fourDigitNumber, 2345);

//   expectClearFourDigits();
//   LedNumber_ClearNumber(fourDigitNumber);
// }

TEST(LedNumber, ShowFourDigitNumber)
{
  LedNumber_SetNumber(fourDigitNumber, 4567);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_UNITS);
  expectSetDigit(SEVEN);
  expectShowDigit();
  LedNumber_ShowNumber(fourDigitNumber);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_TENS);
  expectSetDigit(SIX);
  expectShowDigit();
  LedNumber_ShowNumber(fourDigitNumber);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_HUNDREDS);
  expectSetDigit(FIVE);
  expectShowDigit();
  LedNumber_ShowNumber(fourDigitNumber);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_THOUSANDS);
  expectSetDigit(FOUR);
  expectShowDigit();
  LedNumber_ShowNumber(fourDigitNumber);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_UNITS);
  expectSetDigit(SEVEN);
  expectShowDigit();
  LedNumber_ShowNumber(fourDigitNumber);
}

// TEST(LedNumber, TurnOffLedNumber)
// {
//   expectSetFourDigits(4, 5, 6, 7);
//   LedNumber_SetNumber(fourDigitNumber, 4567);

//   expectTurnOffDigit(fourDigits[LED_UNITS]);
//   expectSetSelectPin(WIRINGLED_UNITS);
//   expectShowDigit(fourDigits[LED_UNITS]);
//   LedNumber_ShowNumber(fourDigitNumber);

//   expectSetSelectPin(WIRINGLED_NONE);
//   LedNumber_TurnOff(fourDigitNumber);

//   expectTurnOffDigit(fourDigits[LED_UNITS]);
//   expectSetSelectPin(WIRINGLED_UNITS);
//   expectShowDigit(fourDigits[LED_UNITS]);
//   LedNumber_ShowNumber(fourDigitNumber);
// }

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

