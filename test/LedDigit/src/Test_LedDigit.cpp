extern "C"
{
  #include "LedDigit.h"
  #include "DataTypes.h"
  #include <string.h>
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedDigit.h"

TEST_GROUP(LedDigit)
{
  LedDigit digit;

  void setup()
  {
    digit = LedDigit_Create();
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
