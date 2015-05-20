#ifndef LineFit_H_
#define LineFit_H_

#include <stdint.h>

typedef struct LineFitStruct * LineFit;

LineFit LineFit_Create(void);
void LineFit_Destroy(LineFit * self);
void LineFit_SetPoint1(LineFit self, int16_t x1, int16_t y1);
void LineFit_SetPoint2(LineFit self, int16_t x2, int16_t y2);
int8_t LineFit_CalculateEquation(LineFit self);
float LineFit_GetOutput(LineFit self, int16_t x);

enum
{
  LINE_FIT_FAIL_VERTICAL_LINE = 0,
  LINE_FIT_SUCCESS = 1
};

#endif
