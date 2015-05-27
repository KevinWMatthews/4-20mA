extern "C"
{
  #include "LedDigit.h"
  #include "DataTypes.h"
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

int8_t virtualPins[PIN_MAX];


TEST_GROUP(LedDigit)
{
  LedDigit digit;
  LedDigit_DataPins dataPins;

  void setup()
  {
    wireVirtualPins();

    digit = LedDigit_Create(&dataPins);
    memset(virtualPins, PIN_UNDEFINED, PIN_MAX);
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

TEST(LedDigit, AllFunctionsCanHandleNullSelf)
{
  LedDigit_ShowDigit(NULL, EIGHT);
  LedDigit_ShowDecimal(NULL);
  LedDigit_ClearAll(NULL);
  LedDigit_ClearDigit(NULL);
  LedDigit_ClearDecimal(NULL);
  LedDigit_CurrentDigit(NULL);
}

TEST(LedDigit, NullDataPins)
{
  LedDigit hasNullPins;
  LedDigit_DataPins nullPins = {};
  hasNullPins = LedDigit_Create(&nullPins);
  LedDigit_ShowDigit(hasNullPins, EIGHT);
  LedDigit_ShowDecimal(hasNullPins);
  LedDigit_ClearAll(hasNullPins); //This might be the only test needed, if any
  LedDigit_ClearDigit(hasNullPins);
  LedDigit_ClearDecimal(hasNullPins);
  LedDigit_Destroy(&hasNullPins);
}

TEST(LedDigit, PointerToDataPinsIsNull)
{
  LedDigit hasNullPinPointer;
  hasNullPinPointer = LedDigit_Create(NULL);
  LedDigit_ShowDigit(hasNullPinPointer, EIGHT);
  LedDigit_ShowDecimal(hasNullPinPointer);
  LedDigit_ClearAll(hasNullPinPointer);
  LedDigit_ClearDigit(hasNullPinPointer);
  LedDigit_ClearDecimal(hasNullPinPointer);
  LedDigit_Destroy(&hasNullPinPointer);
}

TEST(LedDigit, ClearAll)
{
  LedDigit_ClearAll(digit);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit));
  checkStateOfAllPins(digit, PIN_OFF);
}

TEST(LedDigit, ClearDigit)
{
  LedDigit_ClearDigit(digit);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit))
  LONGS_EQUAL(PIN_UNDEFINED, virtualPins[PIN5]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN10]);
}

TEST(LedDigit, ClearDecimal)
{
  LedDigit_ClearDecimal(digit);
  LONGS_EQUAL(PIN_OFF, virtualPins[PIN5]);
  LONGS_EQUAL(PIN_UNDEFINED, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_UNDEFINED, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_UNDEFINED, virtualPins[PIN4]);
  LONGS_EQUAL(PIN_UNDEFINED, virtualPins[PIN2]);
  LONGS_EQUAL(PIN_UNDEFINED, virtualPins[PIN1]);
  LONGS_EQUAL(PIN_UNDEFINED, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_UNDEFINED, virtualPins[PIN10]);
}

TEST(LedDigit, ShowNothing)
{
  LedDigit_ShowDigit(digit, NOTHING);
  LONGS_EQUAL(NOTHING, LedDigit_CurrentDigit(digit))
  checkStateOfAllPins(digit, PIN_OFF);
}

TEST(LedDigit, ShowZero)
{
  LedDigit_ShowDigit(digit, ZERO);
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
  LONGS_EQUAL(ONE, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
}

TEST(LedDigit, ShowTwo)
{
  LedDigit_ShowDigit(digit, TWO);
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
  LONGS_EQUAL(FOUR, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN9]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN10]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
}

TEST(LedDigit, ShowFive)
{
  LedDigit_ShowDigit(digit, FIVE);
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
  LONGS_EQUAL(SEVEN, LedDigit_CurrentDigit(digit));
  LONGS_EQUAL(PIN_ON, virtualPins[PIN7]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN6]);
  LONGS_EQUAL(PIN_ON, virtualPins[PIN4]);
}

TEST(LedDigit, ShowEight)
{
  LedDigit_ShowDigit(digit, EIGHT);
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
