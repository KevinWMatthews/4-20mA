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
  CBI(ADMUX, 7);
  CBI(ADMUX, 6);
  //Right-adjust results
  CBI(ADMUX, 5);

  //Select ADC channel 0, no gain
  CBI(ADMUX, 4);
  CBI(ADMUX, 3);
  CBI(ADMUX, 2);
  CBI(ADMUX, 1);
  CBI(ADMUX, 0);

  //Set Prescaler
  SBI(ADCSR, 2);
  SBI(ADCSR, 1);
  CBI(ADCSR, 0);

  //Disable interrupt
  CBI(ADCSR, 3);

  //Single conversion modes
  CBI(ADCSR, 5);

  //Enable adc
  SBI(ADCSR, 7);

  DDRA = LEDPIN | L1 | L2 | L3 | L4 | L5;

  PORTA = L1 | L2 | L3 | L4 | L5;
  _delay_ms(500);
  PORTA = 0;

  //First conversion for internal initialization
  SBI(ADCSR, 6);

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
