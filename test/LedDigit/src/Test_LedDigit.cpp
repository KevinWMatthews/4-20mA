extern "C"
{
  #include "LedDigit.h"
  #include "DataTypes.h"
  #include <string.h>
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedDigit.h"

static int8_t virtualPins[10];

TEST_GROUP(LedDigit)
{
  LedDigit digit;

  void setup()
  {
    memset(virtualPins, 0, 10);
    digit = LedDigit_Create();
    for (int i = 1; i <= 10; i++)
    {
      LedDigit_WirePins(digit, i, &virtualPins[i-1]);
    }
  }

  void teardown()
  {
    LedDigit_Destroy(&digit);
  }
};

//*** The tests! ***/
TEST(LedDigit, Create)
{
  //TODO learn how to detect a memory leak
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

TEST(LedDigit, DigitClearAfterInit)
{
  LONGS_EQUAL(0, virtualPins[0]);
  LONGS_EQUAL(LED_DIGIT_NO_DIGIT, LedDigit_CurrentDigit(digit));
}

TEST(LedDigit, SetDigit_8)
{
  LedDigit_SetDigit(digit, LED_DIGIT_8);
  LONGS_EQUAL(LED_DIGIT_8, LedDigit_CurrentDigit(digit))
  //This is nasty. Need a wrapper so that we can test pins directly
  LONGS_EQUAL(1, virtualPins[0]);
  LONGS_EQUAL(1, virtualPins[1]);
  LONGS_EQUAL(1, virtualPins[3]);
  LONGS_EQUAL(1, virtualPins[4]);
  LONGS_EQUAL(1, virtualPins[5]);
  LONGS_EQUAL(1, virtualPins[6]);
  LONGS_EQUAL(1, virtualPins[8]);
  LONGS_EQUAL(1, virtualPins[9]);
}
