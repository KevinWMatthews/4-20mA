extern "C"
{
  #include "ChipFunctions.h"
  #include <avr/interrupt.h>
  #include <avr/io.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_ChipFunctions.h"

TEST_GROUP(ChipFunctions)
{
  void setup()
  {
    SREG = 0;
    CLKPR = 0;
  }

  void teardown()
  {
  }
};

TEST(ChipFunctions, AllRegistersZeroAfterSetup)
{
  BYTES_EQUAL(0, SREG);
  BYTES_EQUAL(0, CLKPR);
}

TEST(ChipFunctions, EnableGlobalInterrupts_OtherBitsNotSet)
{
  ChipFunctions_EnableGlobalInterrupts();
  BYTES_EQUAL(0x80, SREG);
}

TEST(ChipFunctions, DisbleGlobalInterrupts_OtherBitsNotCleared)
{
  SREG = 0xff;
  ChipFunctions_DisableGlobalInterrupts();
  BYTES_EQUAL(0xff & ~0x80, SREG);
}

TEST(ChipFunctions, CpuPrescaleFactorCanSetAllBits)
{
  //0x0f isn't a valid prescaler value, so test all bits in two steps
  ChipFunctions_SetCpuPrescaler(CF_CPU_PRESCALE_FACTOR_256);
  BYTES_EQUAL(0x08, CLKPR);
  ChipFunctions_SetCpuPrescaler(CF_CPU_PRESCALE_FACTOR_128);
  BYTES_EQUAL(0x07, CLKPR);
}

TEST(ChipFunctions, CpuPrescaleFactorCanClearAllBits)
{
  CLKPR = 0xff;
  ChipFunctions_SetCpuPrescaler(CF_CPU_PRESCALE_FACTOR_1);
  BYTES_EQUAL(0x00, CLKPR);
}
