#ifndef AtoD_H_
#define AtoD_H_

#include <stdint.h>
#include "DataTypes.h"

enum
{
  ATOD_BUSY = 1
};

int8_t AtoD_Read(void);

#endif
