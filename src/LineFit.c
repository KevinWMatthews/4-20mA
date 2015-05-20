#include "LineFit.h"
#include <stdlib.h>
#include "DataTypes.h"

typedef struct LineFitStruct
{
  int16_t x1;
  int16_t y1;
  int16_t x2;
  int16_t y2;
  float m;
  float b;
} LineFitStruct;

LineFit LineFit_Create(void)
{
  LineFit self = calloc(1, sizeof(LineFitStruct));
  self->m = 0.0f;
  self->b = 0.0f;
  return self;
}

void LineFit_Destroy(LineFit * self)
{
  CHECK_NULL(self);
  free(*self);
  *self = NULL;
}

void LineFit_SetPoint1(LineFit self, int16_t x1, int16_t y1)
{
  CHECK_NULL(self);
  self->x1 = x1;
  self->y1 = y1;
}

void LineFit_SetPoint2(LineFit self, int16_t x2, int16_t y2)
{
  CHECK_NULL(self);
  self->x2 = x2;
  self->y2 = y2;
}

int8_t LineFit_CalculateEquation(LineFit self)
{
  CHECK_NULL_RETURN_VALUE(self, LINE_FIT_FAIL_VERTICAL_LINE);
  if (self->x2 == self->x1)
  {
    return LINE_FIT_FAIL_VERTICAL_LINE;
  }
  self->m = (float)(self->y2 - self->y1) / (self->x2 - self->x1);
  self->b = (float)self->y1 - (self->m * self->x1);
  return LINE_FIT_SUCCESS;
}

float LineFit_GetOutput(LineFit self, int16_t x)
{
  CHECK_NULL_RETURN_VALUE(self, 0.0);
  return (self->m * x) + self->b;
}
