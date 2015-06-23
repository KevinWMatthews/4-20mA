extern "C"
{
  #include "LedDigit.h"
  #include <string.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedDigit.h"

enum
{
  PIN1 = 0,
  PIN2 = 1,
  PIN4 = 2,
  PIN5 = 3,
  PIN6 = 4,
  PIN7 = 5,
  PIN9 = 6,
  PIN10 = 7,
  PIN_MAX = 8
};


static uint8_t virtualRegisters[PIN_MAX];
static uint8_t virtualSelectPin;

TEST_GROUP(LedDigit)
{
  LedDigit digit;
  LedDigit_DataPins dataPins;
  Pin selectPin;

  void setup()
  {
    //Too klutzy?
    dataPins.pin1 = Pin_Create(&virtualRegisters[0], 1<<(0));
    dataPins.pin2 = Pin_Create(&virtualRegisters[1], 1<<(1));
    dataPins.pin4 = Pin_Create(&virtualRegisters[2], 1<<(2));
    dataPins.pin5 = Pin_Create(&virtualRegisters[3], 1<<(3));
    dataPins.pin6 = Pin_Create(&virtualRegisters[4], 1<<(4));
    dataPins.pin7 = Pin_Create(&virtualRegisters[5], 1<<(5));
    dataPins.pin9 = Pin_Create(&virtualRegisters[6], 1<<(6));
    dataPins.pin10 = Pin_Create(&virtualRegisters[7], 1<<(7));

    selectPin = Pin_Create(&virtualSelectPin, 0);
    digit = LedDigit_Create(&dataPins, selectPin);
  }

  void teardown()
  {
    LedDigit_Destroy(&digit);
  }

  void checkStateOfAllVirtualRegisters(PinState state)
  {
    for (int i = 0; i < PIN_MAX; i++)
    {
      LONGS_EQUAL(state, virtualRegisters[i]);
    }
  }

  void callAllFunctions(LedDigit self, LedDigit_DisplayDigit number)
  {
    //Other than Create() and Destroy()
    LedDigit_SetDigit(self, number);
    LedDigit_SetDecimal(self);
    LedDigit_ClearDigit(self);
    LedDigit_ClearDecimal(self);
    LedDigit_ClearAll(self);
    LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(self));
    CHECK_FALSE(LedDigit_IsDecimalShown(self));
    LedDigit_UpdateLed(self);
    LedDigit_TurnLedOff(self);
  }
};

//*** The tests! ***/
//Initialization and NULL pointers
TEST(LedDigit, Create)
{
  checkStateOfAllVirtualRegisters(PIN_LOW);
  LONGS_EQUAL(PIN_LOW, Pin_GetState(selectPin));
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

TEST(LedDigit, AllFunctionsCanHandleNullSelf)
{
  callAllFunctions(NULL, EIGHT);
}

TEST(LedDigit, NullDataPins)
{
  LedDigit hasNullPins;
  LedDigit_DataPins nullPins = {};
  hasNullPins = LedDigit_Create(&nullPins, selectPin);
  callAllFunctions(hasNullPins, EIGHT);
  LedDigit_Destroy(&hasNullPins);
}

TEST(LedDigit, PointerToDataPinsIsNull)
{
  LedDigit hasNullPinPointer;
  hasNullPinPointer = LedDigit_Create(NULL, selectPin);
  callAllFunctions(hasNullPinPointer, EIGHT);
  LedDigit_Destroy(&hasNullPinPointer);
}

TEST(LedDigit, PointerToSelectPinIsNull)
{
  LedDigit hasNullSelectPointer;
  hasNullSelectPointer = LedDigit_Create(&dataPins, NULL);
  callAllFunctions(hasNullSelectPointer, EIGHT);
  LedDigit_Destroy(&hasNullSelectPointer);
}


//Functionality
TEST(LedDigit, SetDigitThatWillBeShown)
{
  LedDigit_SetDigit(digit, SEVEN);
  LONGS_EQUAL(SEVEN, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_LOW, Pin_GetState(selectPin));
}

TEST(LedDigit, SetDecimal)
{
  LedDigit_SetDecimal(digit);
  CHECK_TRUE(LedDigit_IsDecimalShown(digit));
  LONGS_EQUAL(PIN_LOW, Pin_GetState(selectPin));
}

TEST(LedDigit, ClearDigit)
{
  LedDigit_ClearDigit(digit);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_LOW, Pin_GetState(selectPin));
}

TEST(LedDigit, ClearDecimal)
{
  LedDigit_ClearDecimal(digit);
  CHECK_FALSE(LedDigit_IsDecimalShown(digit));
  LONGS_EQUAL(PIN_LOW, Pin_GetState(selectPin));
}

TEST(LedDigit, ClearAll)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  LedDigit_ClearAll(digit);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
  CHECK_FALSE(LedDigit_IsDecimalShown(digit));
  LONGS_EQUAL(PIN_LOW, Pin_GetState(selectPin));
}

TEST(LedDigit, ShowNothing)
{
  LedDigit_SetDigit(digit, NOTHING);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
  checkStateOfAllVirtualRegisters(PIN_LOW);
}

TEST(LedDigit, ShowZero)
{
  LedDigit_SetDigit(digit, ZERO);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowOne)
{
  LedDigit_SetDigit(digit, ONE);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowTwo)
{
  LedDigit_SetDigit(digit, TWO);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowThree)
{
  LedDigit_SetDigit(digit, THREE);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowFour)
{
  LedDigit_SetDigit(digit, FOUR);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowFive)
{
  LedDigit_SetDigit(digit, FIVE);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowSix)
{
  LedDigit_SetDigit(digit, SIX);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowSeven)
{
  LedDigit_SetDigit(digit, SEVEN);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowEight)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowNine)
{
  LedDigit_SetDigit(digit, NINE);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ShowDecimal)
{
  LedDigit_SetDecimal(digit);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, UpdateLedAndDecimal)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, TurnLedOff)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  LedDigit_UpdateLed(digit);
  LedDigit_TurnLedOff(digit);

  LONGS_EQUAL(PIN_LOW, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ChangeDigitsWhileLedIsOn)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  LedDigit_UpdateLed(digit);

  LedDigit_SetDigit(digit, ONE);
  LedDigit_ClearDecimal(digit);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, ClearLedWhenLedIsOn)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  LedDigit_UpdateLed(digit);

  LedDigit_ClearDigit(digit);
  LedDigit_ClearDecimal(digit);
  LedDigit_UpdateLed(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN10] >> PIN10);
  LONGS_EQUAL(PIN_LOW, virtualRegisters[PIN5] >> PIN5);
}

TEST(LedDigit, PinsDontUpdateUntilUpdateIsCalled)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_SetDecimal(digit);
  LedDigit_UpdateLed(digit);

  LedDigit_ClearDigit(digit);
  LedDigit_ClearDecimal(digit);

  LONGS_EQUAL(PIN_HIGH, Pin_GetState(selectPin));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN7] >> PIN7);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN6] >> PIN6);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN4] >> PIN4);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN2] >> PIN2);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN1] >> PIN1);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN9] >> PIN9);
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN10] >> (PIN10));
  LONGS_EQUAL(PIN_HIGH, virtualRegisters[PIN5] >> PIN5);
}
