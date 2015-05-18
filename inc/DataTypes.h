#ifndef DataTypes_H_
#define DataTypes_H_

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

#endif
