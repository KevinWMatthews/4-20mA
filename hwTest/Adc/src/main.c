#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 8000000UL     /* 8MHz internal crystal */
#endif

#include "Adc.h"
#include "AdcWiring.h"
#include <util/delay.h>
#include <avr/io.h>

#include "BitManip.h"

#define LEDPIN (1<<PA7)
#define L1 (1<<PA1)
#define L2 (1<<PA2)
#define L3 (1<<PA4)
#define L4 (1<<PA5)
#define L5 (1<<PA6)

int main(void)
{
  int8_t returnCode;
  int16_t reading = 0;

  int8_t low, high;

  Adc_HwSetup();
  //AVCC is reference voltage
  CLEAR_BIT_NUMBER(ADMUX, 7);
  CLEAR_BIT_NUMBER(ADMUX, 6);
  //Right-adjust results
  CLEAR_BIT_NUMBER(ADMUX, 5);

  //Select ADC channel 0, no gain
  CLEAR_BIT_NUMBER(ADMUX, 4);
  CLEAR_BIT_NUMBER(ADMUX, 3);
  CLEAR_BIT_NUMBER(ADMUX, 2);
  CLEAR_BIT_NUMBER(ADMUX, 1);
  CLEAR_BIT_NUMBER(ADMUX, 0);

  //Set Prescaler
  SET_BIT_NUMBER(ADCSR, 2);
  SET_BIT_NUMBER(ADCSR, 1);
  CLEAR_BIT_NUMBER(ADCSR, 0);

  //Disable interrupt
  CLEAR_BIT_NUMBER(ADCSR, 3);

  //Single conversion modes
  CLEAR_BIT_NUMBER(ADCSR, 5);

  //Enable adc
  SET_BIT_NUMBER(ADCSR, 7);

  DDRA = LEDPIN | L1 | L2 | L3 | L4 | L5;

  PORTA = L1 | L2 | L3 | L4 | L5;
  _delay_ms(500);
  PORTA = 0;

  //First conversion for internal initialization
  SET_BIT_NUMBER(ADCSR, 6);

  while (1)
  {
    PORTA = 0;
    _delay_ms(100);

    do
    {
      returnCode = Adc_StartConversion();
    } while (returnCode != ADC_CONVERSION_STARTED);

    do
    {
      _delay_ms(50);    //Calculate this value using ADC clock cycles and the CPU speed
      returnCode = Adc_Read(&reading);
    } while (returnCode != ADC_READ_SUCCESS);


    PORTA |= LEDPIN;
    if (reading < 200)
    {
      PORTA |= L1;
    }
    else if (reading >= 200 && reading < 400)
    {
      PORTA |= L2;
    }
    else if (reading >= 400 && reading < 600)
    {
      PORTA |= L3;
    }
    else if (reading >= 600 && reading < 800)
    {
      PORTA |= L4;
    }
    else if (reading >= 800)
    {
      PORTA |= L5;
    }
    _delay_ms(2000);
  }
}
