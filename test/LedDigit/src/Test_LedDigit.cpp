extern "C"
{
  #include "LedDigit.h"
  #include "DataTypes.h"
  #include <string.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedDigit.h"

int8_t virtualPins[PIN_MAX];

TEST_GROUP(LedDigit)
{
  LedDigit digit;

  void setup()
  {
    digit = LedDigit_Create();
    for (int i = 0; i < PIN_MAX; i++)
    {
      LedDigit_WirePin(digit, (LedDigit_PinNumber)i, &virtualPins[i]);
    }

    memset(virtualPins, PIN_UNDEFINED, PIN_MAX);
  }

  void teardown()
  {
    LedDigit_Destroy(&digit);
  }

  void checkStateOfAllPins(LedDigit self, Pin state)
  {
    for (int i = 0; i < PIN_MAX; i++)
    {
      LONGS_EQUAL(state, virtualPins[i]);
    }
  }
};

//*** The tests! ***/
TEST(LedDigit, Create)
{
  //TODO learn how to detect a memory leak
  checkStateOfAllPins(digit, PIN_UNDEFINED);
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

TEST(LedDigit, AllFunctionsCanHandleNull)
{
  LedDigit_WirePin(NULL, PIN1, virtualPins);
  LedDigit_WirePin(digit, PIN1, NULL);
  LedDigit_ShowDigit(NULL, EIGHT);
  LedDigit_ShowDecimal(NULL);
  LedDigit_Clear(NULL);
}

TEST(LedDigit, WontShowDigitIfPinsWiredToNull)
{
  LedDigit nullWires = LedDigit_Create();
  LedDigit_ShowDigit(nullWires, EIGHT);
  LedDigit_ShowDecimal(nullWires);
}

TEST(LedDigit, Clear)
{
  LedDigit_Clear(digit);
  checkStateOfAllPins(digit, PIN_OFF);
}

TEST(LedDigit, ShowNothing)
{
  LedDigit_ShowDigit(digit, NOTHING);
  checkStateOfAllPins(digit, PIN_OFF);
}

TEST(LedDigit, ShowOne)
{
  LedDigit_ShowDigit(digit, ONE);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
}

TEST(LedDigit, ShowTwo)
{
  LedDigit_ShowDigit(digit, TWO);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
}

TEST(LedDigit, ShowThree)
{
  LedDigit_ShowDigit(digit, THREE);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
}

TEST(LedDigit, ShowFour)
{
  LedDigit_ShowDigit(digit, FOUR);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
}

TEST(LedDigit, ShowFive)
{
  LedDigit_ShowDigit(digit, FIVE);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN2]);
}

TEST(LedDigit, ShowSix)
{
  LedDigit_ShowDigit(digit, SIX);
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
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
}

TEST(LedDigit, ShowEight)
{
  LedDigit_ShowDigit(digit, EIGHT);
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
