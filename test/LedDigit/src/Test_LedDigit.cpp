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

  void checkStateOfDataPins(LedDigit self, Pin state)
  {
    for (int i = 0; i < PIN_MAX; i++)
    {
      LONGS_EQUAL(state, virtualPins[i]);
    }
  }

  void callAllFunctions(LedDigit self, LedDigit_DisplayDigit number)
  {
    //Other than Create() and Destroy()
    LedDigit_ShowDigit(self, number);
    LedDigit_ShowDecimal(self);
    LedDigit_ClearAll(self);
    LedDigit_ClearDigit(self);
    LedDigit_ClearDecimal(self);
    LedDigit_CurrentDigit(self);
  }
};

//*** The tests! ***/
TEST(LedDigit, Create)
{
  //TODO learn how to detect a memory leak
  checkStateOfDataPins(digit, PIN_OFF);
  LONGS_EQUAL(PIN_OFF, selectPin);
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

TEST(LedDigit, ClearAll)
{
  LedDigit_ClearAll(digit);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
  checkStateOfDataPins(digit, PIN_OFF);
}

TEST(LedDigit, ClearDigit)
{
  LedDigit_ClearDigit(digit);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
  checkStateOfDataPins(digit, PIN_OFF);
}

TEST(LedDigit, ClearDecimal)
{
  LedDigit_ClearDecimal(digit);
  checkStateOfDataPins(digit, PIN_OFF);
}

TEST(LedDigit, ShowNothing)
{
  LedDigit_ShowDigit(digit, NOTHING);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
  checkStateOfDataPins(digit, PIN_OFF);
}

TEST(LedDigit, ShowZero)
{
  LedDigit_ShowDigit(digit, ZERO);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(ZERO, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
}

TEST(LedDigit, ShowOne)
{
  LedDigit_ShowDigit(digit, ONE);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(ONE, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
}

TEST(LedDigit, ShowTwo)
{
  LedDigit_ShowDigit(digit, TWO);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(TWO, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
}

TEST(LedDigit, ShowThree)
{
  LedDigit_ShowDigit(digit, THREE);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(THREE, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
}

TEST(LedDigit, ShowFour)
{
  LedDigit_ShowDigit(digit, FOUR);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(FOUR, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
}

TEST(LedDigit, ShowFive)
{
  LedDigit_ShowDigit(digit, FIVE);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(FIVE, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
}

TEST(LedDigit, ShowSix)
{
  LedDigit_ShowDigit(digit, SIX);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(SIX, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
}

TEST(LedDigit, ShowSeven)
{
  LedDigit_ShowDigit(digit, SEVEN);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(SEVEN, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
}

TEST(LedDigit, ShowEight)
{
  LedDigit_ShowDigit(digit, EIGHT);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(EIGHT, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
}

TEST(LedDigit, ShowNine)
{
  LedDigit_ShowDigit(digit, NINE);
  LONGS_EQUAL(PIN_ON, selectPin);
  LONGS_EQUAL(NINE, LedDigit_CurrentDigit(digit))
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
}

TEST(LedDigit, ShowDecimal)
{
  LedDigit_ShowDecimal(digit);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN5]);
}
