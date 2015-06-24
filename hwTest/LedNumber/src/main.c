#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 8000000UL     /* 8MHz internal crystal */
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "LedNumber.h"

#define LED_A (1<<PA0)
#define LED_B (1<<PA1)
#define LED_C (1<<PA2)
#define LED_D (1<<PA3)
#define LED_E (1<<PA4)
#define LED_F (1<<PA5)
#define LED_G (1<<PA6)
#define LED_DP 0
#define SELECT_PIN (1<<PA7)

int main(void)
{
  LedNumber number;
  LedDigit digit;
  LedDigit_DataPins pinAddresses;
  Pin selectPin;
  Pin digitPin1, digitPin2, digitPin4, digitPin5, digitPin6, digitPin7, digitPin9, digitPin10;

  DDRA = (LED_A) | (LED_B) | (LED_C) | (LED_D) | (LED_E) | (LED_F) | (LED_G) | (SELECT_PIN);

  digitPin1 = Pin_Create(&PORTA, LED_E);
  digitPin2 = Pin_Create(&PORTA, LED_D);
  digitPin4 = Pin_Create(&PORTA, LED_C);
  digitPin5 = Pin_Create(&PORTA, LED_DP);
  digitPin6 = Pin_Create(&PORTA, LED_B);
  digitPin7 = Pin_Create(&PORTA, LED_A);
  digitPin9 = Pin_Create(&PORTA, LED_F);
  digitPin10 = Pin_Create(&PORTA, LED_G);

  pinAddresses.pin1 = digitPin1;
  pinAddresses.pin2 = digitPin2;
  pinAddresses.pin4 = digitPin4;
  pinAddresses.pin5 = NULL;
  pinAddresses.pin6 = digitPin6;
  pinAddresses.pin7 = digitPin7;
  pinAddresses.pin9 = digitPin9;
  pinAddresses.pin10 = digitPin10;

  selectPin = Pin_Create(&PORTA, SELECT_PIN);

  digit = LedDigit_Create(&pinAddresses, selectPin);

  number = LedNumber_Create(2);
  LedNumber_AddLedDigit(number, digit, LED1);
  LedNumber_AddLedDigit(number, digit, LED2);

  LedNumber_SetNumber(number, 42);

  while (1)
  {
    LedNumber_ShowNumber(number);
    _delay_ms(2000);
  }
}