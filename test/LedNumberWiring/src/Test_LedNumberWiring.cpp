extern "C"
{
  #include "LedNumberWiring.h"
  #include <avr/io.h>
  #include "BitManip.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedNumberWiring.h"

TEST_GROUP(LedNumberWiring)
{
  void setup()
  {
    WIRINGPORT = 0;
    WIRINGDDR = 0;
    LedNumberWiring_HwSetup();
  }

  void teardown()
  {
  }

  void checkMemoryRegisters(uint8_t ddr, uint8_t port)
  {
    uint8_t expectedPort = 0;
    SET_BITMASK_TO(expectedPort, WIRINGPIN_BITMASK, 0xff);
    CLEAR_BITS(expectedPort, (port));
    BYTES_EQUAL(ddr, WIRINGDDR);
    BYTES_EQUAL(expectedPort, WIRINGPORT);
  }
};

TEST(LedNumberWiring, HwSetup)
{
  checkMemoryRegisters(WIRINGPIN_BITMASK, WIRINGPIN_NONE);
}

TEST(LedNumberWiring, SelectNoLed)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_NONE);
  checkMemoryRegisters(WIRINGPIN_BITMASK, WIRINGPIN_NONE);
}

TEST(LedNumberWiring, SelectLed1)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_UNITS);
  checkMemoryRegisters(WIRINGPIN_BITMASK, WIRINGPIN_LED1);
}

TEST(LedNumberWiring, SelectLed2)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_TENS);
  checkMemoryRegisters(WIRINGPIN_BITMASK, WIRINGPIN_LED2);
}

TEST(LedNumberWiring, SelectLed3)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_HUNDREDS);
  checkMemoryRegisters(WIRINGPIN_BITMASK, WIRINGPIN_LED3);
}

TEST(LedNumberWiring, SelectLed4)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_THOUSANDS);
  checkMemoryRegisters(WIRINGPIN_BITMASK, WIRINGPIN_LED4);
}

TEST(LedNumberWiring, SetUpperBound)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_UPPER_BOUND);
  checkMemoryRegisters(WIRINGPIN_BITMASK, WIRINGPIN_NONE);
}

TEST(LedNumberWiring, SetConsecutiveSelectPinsClearsPreviousPins)
{
  LedNumberWiring_SetSelectPin(WIRINGLED_UNITS);
  LedNumberWiring_SetSelectPin(WIRINGLED_TENS);
  checkMemoryRegisters(WIRINGPIN_BITMASK, WIRINGPIN_LED2);
}
