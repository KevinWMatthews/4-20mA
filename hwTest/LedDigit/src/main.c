#include <avr/io.h>
#include "LedDigit.h"

int main(void)
{
  LedDigit digit;
  LedDigit_DataPins pinAddresses = {
    NULL,   //1
    NULL,   //2
    1<<PA5, //4
    NULL,   //5
    1<<PA4, //6
    1<<PA3, //7
    NULL,   //9
    NULL    //10
  };

  DDRA = (1<<PA3) | (1<<PA4) | (1<<PA5);

  digit = LedDigit_Create(&pinAddresses, NULL);
  LedDigit_SetDigit(digit, SEVEN);
  LedDigit_UpdateLed(digit);
  while (1)
  {
    PORTA |= (int)(pinAddresses.pin4);
    // PORTA |= (1<<PA4);
  }
}
