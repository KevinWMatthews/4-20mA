extern "C"
{
  #include "LedDigit.h"
  #include "LedDigitWiring.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_LedDigit.h"


TEST_GROUP(LedDigit)
{
  LedDigit digit;

  void setup()
  {
    expectInitCall();
    LedDigit_HwSetup();
    expectPinCalls(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
    expectPinDecimalPointCall(FALSE);
    digit = LedDigit_Create();
  }

  void teardown()
  {
    LedDigit_Destroy(&digit);
    mock().checkExpectations();
    mock().clear();
  }

  //*** Helper functions ***//
  void expectInitCall(void)
  {
    mock().expectOneCall("LedDigitWiring_Init");
  }

  void expectPinCall(BOOL setPin, LedDigitWiring_Pin pin)
  {
    if (setPin == TRUE)
    {
      mock().expectOneCall("LedDigitWiring_SetPin")
            .withParameter("pin", pin);
    }
    else
    {
      mock().expectOneCall("LedDigitWiring_ClearPin")
            .withParameter("pin", pin);
    }
  }

  //TRUE to set a pin, FALSE to clear a pin
  void expectPinCalls(BOOL pinA, BOOL pinB, BOOL pinC, BOOL pinD, BOOL pinE, BOOL pinF, BOOL pinG)
  {
    expectPinCall(pinA, PIN_A);
    expectPinCall(pinB, PIN_B);
    expectPinCall(pinC, PIN_C);
    expectPinCall(pinD, PIN_D);
    expectPinCall(pinE, PIN_E);
    expectPinCall(pinF, PIN_F);
    expectPinCall(pinG, PIN_G);
  }

  void expectPinDecimalPointCall(BOOL pinDP)
  {
    expectPinCall(pinDP, PIN_DP);
  }
};



//**********************//
//*** Function mocks ***//
//**********************//
void LedDigitWiring_Init(void)
{
  mock().actualCall("LedDigitWiring_Init");
}

void LedDigitWiring_SetPin(LedDigitWiring_Pin pin)
{
  mock().actualCall("LedDigitWiring_SetPin")
        .withParameter("pin", pin);
}

void LedDigitWiring_ClearPin(LedDigitWiring_Pin pin)
{
  mock().actualCall("LedDigitWiring_ClearPin")
        .withParameter("pin", pin);
}


//******************//
//*** Unit Tests ***//
//******************//
//Initialization and NULL pointers
TEST(LedDigit, Create)
{
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
  CHECK_FALSE(LedDigit_IsDecimalShown(digit));
}

TEST(LedDigit, DestroyCanHandleNullPointer)
{
  LedDigit_Destroy(NULL);
}

TEST(LedDigit, DestroyCanHandlePointerToNull)
{
  LedDigit pointer = NULL;
  LedDigit_Destroy(&pointer);
}

TEST(LedDigit, DestroyClearsPointer)
{
  LedDigit_Destroy(&digit);
  POINTERS_EQUAL(NULL, digit);
}

//*** Functionality ***//
TEST(LedDigit, SetDigitThatWillBeShown)
{
  LedDigit_SetDigit(digit, SEVEN);
  LONGS_EQUAL(SEVEN, LedDigit_CurrentDigit(digit));
}

TEST(LedDigit, SetDecimal)
{
  LedDigit_SetDecimal(digit);
  CHECK_TRUE(LedDigit_IsDecimalShown(digit));
}

TEST(LedDigit, ClearDigit)
{
  LedDigit_ClearDigit(digit);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
}

TEST(LedDigit, ClearDecimal)
{
  LedDigit_ClearDecimal(digit);
  CHECK_FALSE(LedDigit_IsDecimalShown(digit));
}

TEST(LedDigit, ClearAll)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  LedDigit_ClearAll(digit);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
  CHECK_FALSE(LedDigit_IsDecimalShown(digit));
}

TEST(LedDigit, ShowNothing)
{
  expectPinCalls(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
  expectPinDecimalPointCall(FALSE);

  LedDigit_SetDigit(digit, NOTHING);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowZero)
{
  LedDigit_SetDigit(digit, ZERO);
  expectPinCalls(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowOne)
{
  LedDigit_SetDigit(digit, ONE);
  expectPinCalls(FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowTwo)
{
  LedDigit_SetDigit(digit, TWO);
  expectPinCalls(TRUE, TRUE, FALSE, TRUE, TRUE, FALSE, TRUE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowThree)
{
  LedDigit_SetDigit(digit, THREE);
  expectPinCalls(TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, TRUE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowFour)
{
  LedDigit_SetDigit(digit, FOUR);
  expectPinCalls(FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, TRUE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowFive)
{
  LedDigit_SetDigit(digit, FIVE);
  expectPinCalls(TRUE, FALSE, TRUE, TRUE, FALSE, TRUE, TRUE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowSix)
{
  LedDigit_SetDigit(digit, SIX);
  expectPinCalls(TRUE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowSeven)
{
  LedDigit_SetDigit(digit, SEVEN);
  expectPinCalls(TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowEight)
{
  LedDigit_SetDigit(digit, EIGHT);
  expectPinCalls(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowNine)
{
  LedDigit_SetDigit(digit, NINE);
  expectPinCalls(TRUE, TRUE, TRUE, FALSE, FALSE, TRUE, TRUE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ShowDecimalOnly)
{
  LedDigit_SetDecimal(digit);
  expectPinCalls(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
  expectPinDecimalPointCall(TRUE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, UpdateLedAndDecimal)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  expectPinCalls(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
  expectPinDecimalPointCall(TRUE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, TurnLedOff)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  expectPinCalls(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
  expectPinDecimalPointCall(TRUE);
  LedDigit_UpdateLed(digit);

  expectPinCalls(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_TurnLedOff(digit);
}

TEST(LedDigit, ChangeDigitsWhileLedIsOn)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  expectPinCalls(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
  expectPinDecimalPointCall(TRUE);
  LedDigit_UpdateLed(digit);

  LedDigit_SetDigit(digit, ONE);
  LedDigit_ClearDecimal(digit);
  expectPinCalls(FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, ClearLedWhenLedIsOn)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  expectPinCalls(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
  expectPinDecimalPointCall(TRUE);
  LedDigit_UpdateLed(digit);

  LedDigit_ClearDigit(digit);
  LedDigit_ClearDecimal(digit);

  expectPinCalls(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
  expectPinDecimalPointCall(FALSE);
  LedDigit_UpdateLed(digit);
}

TEST(LedDigit, PinsDontUpdateUntilUpdateIsCalled)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  expectPinCalls(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
  expectPinDecimalPointCall(TRUE);
  LedDigit_UpdateLed(digit);

  LedDigit_ClearDigit(digit);
  LedDigit_ClearDecimal(digit);
}
