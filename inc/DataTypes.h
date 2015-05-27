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

#endif
