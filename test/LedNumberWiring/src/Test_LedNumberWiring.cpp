extern "C"
{
  #include "LedNumberWiring.h"
  #include <avr/io.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedNumberWiring.h"

TEST_GROUP(LedNumberWiring)
{
  void setup()
  {
    PORTB = 0;
    DDRB = 0;
    LedNumberWiring_HwSetup();
  }

  void teardown()
  {
  }

  void checkMemoryRegisters(uint8_t ddrb, uint8_t portb)
  {
    LONGS_EQUAL(ddrb, DDRB);
    LONGS_EQUAL(portb, PORTB);
  }
};

TEST(LedNumberWiring, InitCheck)
{
  checkMemoryRegisters(0x0f, 0x0f);
}

TEST(LedNumberWiring, SelectNoLed)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_NONE);
  checkMemoryRegisters(0x0f, 0x0f);
}

TEST(LedNumberWiring, SelectLed1)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_UNITS);
  checkMemoryRegisters(0x0f, 0x0e);
}

TEST(LedNumberWiring, SelectLed2)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_TENS);
  checkMemoryRegisters(0x0f, 0x0d);
}

TEST(LedNumberWiring, SelectLed3)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_HUNDREDS);
  checkMemoryRegisters(0x0f, 0x0b);
}

TEST(LedNumberWiring, SelectLed4)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_THOUSANDS);
  checkMemoryRegisters(0x0f, 0x07);
}

TEST(LedNumberWiring, SetUpperBound)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_UPPER_BOUND);
  checkMemoryRegisters(0x0f, 0x0f);
}

TEST(LedNumberWiring, SetConsecutiveSelectPins)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_UNITS);
  LedNumberWiring_SetSelectPin(WIRINGLED_TENS);
  checkMemoryRegisters(0x0f, 0x0d);
}
