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


//Function return values
typedef enum
{
  PIN_NULL_POINTER = -66,
  PIN_UNDEFINED = -1,
  PIN_LOW = 0,
  PIN_HIGH  = 1
} PinState;

#define NULL_POINTER 66


typedef struct PinStruct * Pin;

//This data type is designed for pins that will be in existence for the duration
//of the program!
Pin Pin_Create(uint8_t * address, uint8_t bitmask);
void Pin_Destroy(Pin * self);

uint8_t * Pin_GetAddress(Pin self);
uint8_t Pin_GetBitmask(Pin self);
PinState Pin_GetState(Pin self);
void Pin_SetState(Pin self, PinState state);

#endif
