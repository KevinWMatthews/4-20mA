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

#define RETURN_IF_NULL(pointer) if ((pointer) == NULL) return
#define RETURN_VALUE_IF_NULL(pointer, retVal) if ((pointer) == NULL) return (retVal)

#endif
