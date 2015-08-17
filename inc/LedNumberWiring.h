#ifndef LedNumberWiring_H_
#define LedNumberWiring_H_



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Edit here to change hardware wiring! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//Currently only 4 LEDs are supported
#define WIRINGDDR         (DDRA)
#define WIRINGPORT        (PORTA)
#define WIRINGPIN_NONE    0
#define WIRINGPIN_LED1    (1<<PA4)
#define WIRINGPIN_LED2    (1<<PA5)
#define WIRINGPIN_LED3    (1<<PA6)
#define WIRINGPIN_LED4    (1<<PA7)
#define WIRINGPIN_ERROR   0xff
#define WIRINGPIN_BITMASK (WIRINGPIN_LED1 | WIRINGPIN_LED2 | WIRINGPIN_LED3 | WIRINGPIN_LED4)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Edit here to change hardware wiring! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//



//******************//
//*** Data types ***//
//******************//
typedef enum
{
  WIRINGLED_NONE        = -1,
  WIRINGLED_UNITS       =  0,
  WIRINGLED_TENS        =  1,
  WIRINGLED_HUNDREDS    =  2,
  WIRINGLED_THOUSANDS   =  3,
  WIRINGLED_UPPER_BOUND =  4
} LedNumberWiring_Place;



//************************//
//*** Public Functions ***//
//************************//
void LedNumberWiring_HwSetup(void);

//Pin selection is mutually exclusive - only one pin will be selected at a time.
//Selecting any new pin unselects all others.
void LedNumberWiring_SetSelectPin(LedNumberWiring_Place place);



#endif
