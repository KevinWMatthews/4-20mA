#ifndef LedNumberWiring_H_
#define LedNumberWiring_H_


typedef enum
{
  WIRINGLED_NONE        = -1,
  WIRINGLED_UNITS       =  0,
  WIRINGLED_TENS        =  1,
  WIRINGLED_HUNDREDS    =  2,
  WIRINGLED_THOUSANDS   =  3,
  WIRINGLED_UPPER_BOUND =  4
} LedNumberWiring_Place;

void LedNumberWiring_HwSetup(void);

//Pin selection is mutually exclusive - only one pin will be selected at a time.
//Selecting any new pin unselects all others.
void LedNumberWiring_SetSelectPin(LedNumberWiring_Place pin);

#endif
