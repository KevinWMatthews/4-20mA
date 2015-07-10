#ifndef LineFit_H_
#define LineFit_H_

#include "DataTypes.h"



//******************//
//*** Data types ***//
//******************//
typedef struct LineFitStruct * LineFit;

enum
{
  LINE_FIT_FAIL_VERTICAL_LINE = -2,
  LINE_FIT_FAIL_NULL_POINTER  = -1,
  LINE_FIT_SUCCESS            = 1
};



//************************//
//*** Public Functions ***//
//************************//
LineFit LineFit_Create(void);
void LineFit_Destroy(LineFit * self);
void LineFit_SetPoint1(LineFit self, int16_t x1, int16_t y1);
void LineFit_SetPoint2(LineFit self, int16_t x2, int16_t y2);
int8_t LineFit_CalculateEquation(LineFit self);
float LineFit_GetOutput(LineFit self, int16_t x);



#endif
