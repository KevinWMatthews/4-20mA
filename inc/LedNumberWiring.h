#ifndef LedNumberWiring_H_
#define LedNumberWiring_H_

#define LED_MAX 4

typedef enum
{
  WIRINGLED_NONE      = -1,
  WIRINGLED_UNITS     =  0,
  WIRINGLED_TENS      =  1,
  WIRINGLED_HUNDREDS  =  2,
  WIRINGLED_THOUSANDS =  3
} LedNumberWiring_Place;

void LedNumberWiring_Init(void);

//Pin selection is mutually exclusive - only one pin will be selected at a time.
//Selecting any new pin unselects all others.
void LedNumberWiring_SetSelectPin(LedNumberWiring_Place pin);

#endif
