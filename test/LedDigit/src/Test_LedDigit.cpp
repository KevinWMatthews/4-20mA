extern "C"
{
  #include "LedDigit.h"
  #include <string.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedDigit.h"

typedef enum
{
  //Pins 3 and 8 are not available for use
  PIN1 = 0,
  PIN2 = 1,
  PIN4 = 2,
  PIN5 = 3,
  PIN6 = 4,
  PIN7 = 5,
  PIN9 = 6,
  PIN10 = 7,
  PIN_MAX = 8
} VirtualPin_PinNumber;

Pin virtualPins[PIN_MAX];


TEST_GROUP(LedDigit)
{
  LedDigit digit;
  LedDigit_DataPins dataPins;
  Pin selectPin;

  void setup()
  {
    wireVirtualPins();
    memset(virtualPins, PIN_UNDEFINED, PIN_MAX);
    selectPin = PIN_UNDEFINED;

    digit = LedDigit_Create(&dataPins, &selectPin);
  }

  void teardown()
  {
    LedDigit_Destroy(&digit);
  }

  void wireVirtualPins(void)
  {
    dataPins.pin1 = &virtualPins[0];
    dataPins.pin2 = &virtualPins[1];
    dataPins.pin4 = &virtualPins[2];
    dataPins.pin5 = &virtualPins[3];
    dataPins.pin6 = &virtualPins[4];
    dataPins.pin7 = &virtualPins[5];
    dataPins.pin9 = &virtualPins[6];
    dataPins.pin10 = &virtualPins[7];
  }

  void checkVirtualPinState(VirtualPin_PinNumber pinNumber, Pin state)
  {
    LONGS_EQUAL(state, virtualPins[pinNumber]);
  }

  void checkStateOfAllDataPins(LedDigit self, Pin state)
  {
    for (int i = 0; i < PIN_MAX; i++)
    {
      LONGS_EQUAL(state, virtualPins[i]);
    }
  }

  void callAllFunctions(LedDigit self, LedDigit_DisplayDigit number)
  {
    //Other than Create() and Destroy()
    LedDigit_SetDigit(self, number);
    LedDigit_SetDigit(self, number);
    LedDigit_ClearAll(self);
    LedDigit_ClearDigit(self);
    LedDigit_ClearDecimal(self);
    LedDigit_CurrentValue(self);
  }
};

//*** The tests! ***/

//Initialization
TEST(LedDigit, Create)
{
  //TODO learn how to detect a memory leak
  checkStateOfAllDataPins(digit, PIN_OFF);
  LONGS_EQUAL(PIN_OFF, selectPin);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentValue(digit));
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
  hasNullPins = LedDigit_Create(&nullPins, &selectPin);
  callAllFunctions(hasNullPins, EIGHT);
  LedDigit_Destroy(&hasNullPins);
}

TEST(LedDigit, PointerToDataPinsIsNull)
{
  LedDigit hasNullPinPointer;
  hasNullPinPointer = LedDigit_Create(NULL, &selectPin);
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
TEST(LedDigit, SetDigitToShow)
{
  LedDigit_SetDigit(digit, SEVEN);
  LONGS_EQUAL(SEVEN, LedDigit_CurrentValue(digit));
}

TEST(LedDigit, SetDecimal)
{
  LedDigit_SetDecimal(digit);
  CHECK_TRUE(LedDigit_IsDecimalShown(digit));
}

TEST(LedDigit, ClearDigit)
{
  LedDigit_ClearDigit(digit);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentValue(digit));
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
  LONGS_EQUAL(NOTHING, LedDigit_CurrentValue(digit));
  CHECK_FALSE(LedDigit_IsDecimalShown(digit));
}

TEST(LedDigit, ShowNothing)
{
  LedDigit_SetDigit(digit, NOTHING);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentValue(digit));
  checkStateOfAllDataPins(digit, PIN_OFF);
}

TEST(LedDigit, ShowZero)
{
  LedDigit_SetDigit(digit, ZERO);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowOne)
{
  LedDigit_SetDigit(digit, ONE);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowTwo)
{
  LedDigit_SetDigit(digit, TWO);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowThree)
{
  LedDigit_SetDigit(digit, THREE);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowFour)
{
  LedDigit_SetDigit(digit, FOUR);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowFive)
{
  LedDigit_SetDigit(digit, FIVE);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowSix)
{
  LedDigit_SetDigit(digit, SIX);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowSeven)
{
  LedDigit_SetDigit(digit, SEVEN);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowEight)
{
  LedDigit_SetDigit(digit, EIGHT);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowNine)
{
  LedDigit_SetDigit(digit, NINE);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
}

TEST(LedDigit, ShowDecimal)
{
  LedDigit_SetDecimal(digit);
  LedDigit_ShowDigit(digit);

  LONGS_EQUAL(PIN_OFF, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN5]);
}
