#ifndef DataTypes_H_
#define DataTypes_H_

#include <stdint.h>

typedef enum
{
  FALSE = 0,
  TRUE =  1
} BOOL;

#ifndef NULL
#define NULL 0
#endif

#define CHECK_NULL(pointer) if ((pointer) == NULL) return
#define CHECK_NULL_RETURN_VALUE(pointer, retVal) if ((pointer) == NULL) return (retVal)

typedef enum
{
  PIN_UNDEFINED = -1,
  PIN_OFF = 0,
  PIN_ON  = 1
} Pin;

typedef Pin * PinAddress;

void setPinState(PinAddress pin, Pin state);

//*********************//
//Function return values
typedef enum
{
  _PIN_NULL_POINTER = -66,
  _PIN_UNDEFINED = -1,
  _PIN_LOW = 0,
  _PIN_HIGH  = 1
} _PinState;

#define NULL_POINTER -66


typedef struct _PinStruct * _Pin;

//This data type is designed for pins that will be in existence for the duration
//of the program!
_Pin Pin_Create(int8_t * address, int8_t bitmask);
void Pin_Destroy(_Pin * self);

int8_t * Pin_GetAddress(_Pin self);
int8_t Pin_GetBitmask(_Pin self);
_PinState Pin_GetState(_Pin self);
void Pin_SetState(_Pin self, _PinState state);

#endif
