#include "LineFit.h"
#include <stdlib.h>
#include "DataTypes.h"

typedef struct LineFitStruct
{
  int x1;
  int y1;
  int x2;
  int y2;
  float m;
  float b;
} LineFitStruct;

LineFit LineFit_Create(void)
{
  LineFit self = calloc(1, sizeof(LineFitStruct));
  return self;
}

void LineFit_Destroy(LineFit * self)
{
  CHECK_NULL(self);
  free(*self);
  *self = NULL;
}
