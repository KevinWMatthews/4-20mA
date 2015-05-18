#ifndef AtoD_H_
#define AtoD_H_

#include <stdint.h>
#include "DataTypes.h"

enum
{
  ATOD_INTERRUPT_FLAG_NOT_SET = -2,
  ATOD_BUSY                   = -1,
  ATOD_CONVERSION_STARTED     = 1
};

int8_t AtoD_StartConversion(void);
int8_t AtoD_Read(int16_t * reading);

#endif
