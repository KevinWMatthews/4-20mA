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
    LedNumberWiring_Init();
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
  LedNumberWring_SetSelectPin(LED_NONE);
  checkMemoryRegisters(0x0f, 0x0f);
}

TEST(LedNumberWiring, SelectLed1)
{
  LedNumberWring_SetSelectPin(LED_1);
  checkMemoryRegisters(0x0f, 0x0e);
}

TEST(LedNumberWiring, SelectLed2)
{
  LedNumberWring_SetSelectPin(LED_2);
  checkMemoryRegisters(0x0f, 0x0d);
}

TEST(LedNumberWiring, SelectLed3)
{
  LedNumberWring_SetSelectPin(LED_3);
  checkMemoryRegisters(0x0f, 0x0b);
}

TEST(LedNumberWiring, SelectLed4)
{
  LedNumberWring_SetSelectPin(LED_4);
  checkMemoryRegisters(0x0f, 0x07);
}

TEST(LedNumberWiring, SetConsecutiveSelectPins)
{
  LedNumberWring_SetSelectPin(LED_1);
  LedNumberWring_SetSelectPin(LED_2);
  checkMemoryRegisters(0x0f, 0x0d);
}
