extern "C"
{
  #include "PinDriver.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_PinDriver.h"

//These values will be provided by the chip and the manufacturers header file.
volatile uint8_t * memoryPointer;
uint8_t memoryRegister;
#define BIT1 0
#define BIT2 1
#define BIT3 2
#define BIT4 3
#define BIT5 4
#define BIT6 5
#define BIT7 6
#define BIT8 7

TEST_GROUP(PinDriver)
{
  void setup()
  {
    memoryRegister = 0;
    memoryPointer = &memoryRegister;
  }

  void teardown()
  {
  }
};

TEST(PinDriver, CheckSetup)
{
  LONGS_EQUAL(memoryRegister, 0);
  POINTERS_EQUAL(&memoryRegister, memoryPointer);
}

TEST(PinDriver, SetLeastSignificatBit)
{
  PinDriver_SetBit(memoryPointer, BIT1);
  LONGS_EQUAL(0x01, memoryRegister);
}

TEST(PinDriver, ClearLeastSignificantBit)
{
  PinDriver_SetBit(memoryPointer, BIT1);
  PinDriver_ClearBit(memoryPointer, BIT1);
  LONGS_EQUAL(0x00, memoryRegister);
}

TEST(PinDriver, SetMostSignificatBit)
{
  PinDriver_SetBit(memoryPointer, BIT8);
  LONGS_EQUAL(0x80, memoryRegister);
}

TEST(PinDriver, ClearMostSignificantBit)
{
  PinDriver_SetBit(memoryPointer, BIT8);
  PinDriver_ClearBit(memoryPointer, BIT8);
  LONGS_EQUAL(0x00, memoryRegister);
}


TEST(PinDriver, SetSeveralBits)
{
  PinDriver_SetBit(memoryPointer, BIT1);
  PinDriver_SetBit(memoryPointer, BIT3);
  PinDriver_SetBit(memoryPointer, BIT5);
  PinDriver_SetBit(memoryPointer, BIT7);
  LONGS_EQUAL(0x55, memoryRegister);
}

TEST(PinDriver, ClearSeveralBits)
{
  PinDriver_SetBit(memoryPointer, BIT1);
  PinDriver_SetBit(memoryPointer, BIT2);
  PinDriver_SetBit(memoryPointer, BIT3);
  PinDriver_SetBit(memoryPointer, BIT4);
  PinDriver_SetBit(memoryPointer, BIT5);
  PinDriver_SetBit(memoryPointer, BIT6);
  PinDriver_SetBit(memoryPointer, BIT7);
  PinDriver_SetBit(memoryPointer, BIT8);

  PinDriver_ClearBit(memoryPointer, BIT1);
  PinDriver_ClearBit(memoryPointer, BIT3);
  PinDriver_ClearBit(memoryPointer, BIT5);
  PinDriver_ClearBit(memoryPointer, BIT7);

  LONGS_EQUAL(0xAA, memoryRegister);
}

TEST(PinDriver, GetPinState)
{
  PinDriver_SetBit(memoryPointer, BIT2);

  LONGS_EQUAL(0x00, PinDriver_IfBit(memoryPointer, BIT1));
  LONGS_EQUAL(0x01, PinDriver_IfBit(memoryPointer, BIT2));
}
