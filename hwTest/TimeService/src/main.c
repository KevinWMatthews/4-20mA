#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "TimeService.h"
#include "DataTypes.h"
#include "BitManip.h"

#define LED_PIN (1<<PA0)


void toggleLed(void * param)
{
  //AT pins support read and write so we can use exclusive OR to toggle the pin
  PORTA = PORTA ^ LED_PIN;
}


int main(void)
{
  PeriodicAlarm flashingLed;
  PeriodicAlarmCallback callback = toggleLed;

  TimeService_Create();
  flashingLed = TimeService_AddPeriodicAlarm(callback, 1000);
  TimeService_ActivatePeriodicAlarm(flashingLed);

  //LED setup
  DDRA = LED_PIN;     // Configure pin as output
  // 8MHz system clock / (64 Prescaler * 125 compare value) = 1000 Hz / match
  CBI(TCCR1B, CS13);  //Set Prescaler to 0111 for SystemClock/64
  SBI(TCCR1B, CS12);
  SBI(TCCR1B, CS11);
  SBI(TCCR1B, CS10);
  OCR1C = 125;        //Set Timer Compare value
  SBI(TCCR1B, 7);     //Clear timer on match
  SBI(TCCR1B, 6);     //Reset Timer1
  SBI(TIMSK, 6);      //Enable Timer1 Compare interrupts
  SBI(SREG, 7);       //Enable global interrupts [can use sei()]

  while(1)
  {
    TimeService_ServiceSingleCallback(flashingLed, NULL);
  }
}

ISR(TIMER1_CMPA_vect)
{
  TimeService_TimerTick();
}
