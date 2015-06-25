extern "C"
{
  #include "LedDigitWiring.h"
  #include <avr/io.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedDigitWiring.h"

TEST_GROUP(LedDigitWiring)
{
  void setup()
  {
    DDRA = 0;
    PORTA = 0;
  }

  void teardown()
  {
  }

  void checkMemoryRegisters(uint8_t ddra, uint8_t porta)
  {
    LONGS_EQUAL(ddra, DDRA);
    LONGS_EQUAL(porta, PORTA);
  }
};

TEST(LedDigitWiring, SetupCheck)
{
  checkMemoryRegisters(0, 0);
}

TEST(LedDigitWiring, InitializeGpioToOutputs)
{
  LedDigitWiring_Init();
  checkMemoryRegisters(0xff, 0);
}

TEST(LedDigitWiring, SetPinA)
{
  LedDigitWiring_SetPin(PIN_A);
  checkMemoryRegisters(0, 0x01);
}

TEST(LedDigitWiring, ClearPinA)
{
  LedDigitWiring_SetPin(PIN_A);
  LedDigitWiring_ClearPin(PIN_A);
  checkMemoryRegisters(0, 0);
}

TEST(LedDigitWiring, SetPinB)
{
  LedDigitWiring_SetPin(PIN_B);
  checkMemoryRegisters(0, 0x02);
}

TEST(LedDigitWiring, SetPinC)
{
  LedDigitWiring_SetPin(PIN_C);
  checkMemoryRegisters(0, 0x04);
}

TEST(LedDigitWiring, SetPinD)
{
  LedDigitWiring_SetPin(PIN_D);
  checkMemoryRegisters(0, 0x08);
}

TEST(LedDigitWiring, SetPinE)
{
  LedDigitWiring_SetPin(PIN_E);
  checkMemoryRegisters(0, 0x10);
}

TEST(LedDigitWiring, SetPinF)
{
  LedDigitWiring_SetPin(PIN_F);
  checkMemoryRegisters(0, 0x20);
}

TEST(LedDigitWiring, SetPinG)
{
  LedDigitWiring_SetPin(PIN_G);
  checkMemoryRegisters(0, 0x40);
}

TEST(LedDigitWiring, SetPinDecimalPoint)
{
  LedDigitWiring_SetPin(PIN_DP);
  checkMemoryRegisters(0, 0x80);
}
