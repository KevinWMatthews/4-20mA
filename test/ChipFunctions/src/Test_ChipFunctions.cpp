extern "C"
{
  #include "ChipFunctions.h"
  #include <avr/interrupt.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_ChipFunctions.h"

TEST_GROUP(ChipFunctions)
{
  void setup()
  {
    SREG = 0;
  }

  void teardown()
  {
  }
};

TEST(ChipFunctions, EnableGlobalInterrupts_OtherBitsNotSet)
{
  ChipFunctions_EnableGlobalInterrupts();
  BYTES_EQUAL(0x80, SREG);
}

TEST(ChipFunctions, EnableGlobalInterrupts_OtherBitsNotCleared)
{
  SREG = 0xff;
  ChipFunctions_DisableGlobalInterrupts();
  BYTES_EQUAL(0xff & ~0x80, SREG);
}
