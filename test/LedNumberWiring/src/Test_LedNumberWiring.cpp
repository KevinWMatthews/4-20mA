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

TEST(LedNumberWiring, SetupCheck)
{
  checkMemoryRegisters(0, 0);
}

TEST(LedNumberWiring, InitCheck)
{
  LedNumberWiring_Init();
  checkMemoryRegisters(0x78, 0);  //Pins 3, 4, 5, 6
}

TEST(LedNumberWiring, SelectNoLed)
{
  LedNumberWring_SetSelectPin(LED_NONE);
  checkMemoryRegisters(0, 0);
}

TEST(LedNumberWiring, SelectLed1)
{
  LedNumberWring_SetSelectPin(LED_1);
  checkMemoryRegisters(0, 0x08);
}

TEST(LedNumberWiring, SelectLed2)
{
  LedNumberWring_SetSelectPin(LED_2);
  checkMemoryRegisters(0, 0x10);
}

TEST(LedNumberWiring, SelectLed3)
{
  LedNumberWring_SetSelectPin(LED_3);
  checkMemoryRegisters(0, 0x20);
}

TEST(LedNumberWiring, SelectLed4)
{
  LedNumberWring_SetSelectPin(LED_4);
  checkMemoryRegisters(0, 0x40);
}
