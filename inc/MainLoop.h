#ifndef MainLoop_H_
#define MainLoop_H_

#include "LineFit.h"
#include "DataTypes.h"

void MainLoop_AtodConversion(void);
int8_t MainLoop_GetAtodConversionStatus(void);

void MainLoop_GetReading(LineFit outputModel, float * reading);

//Included to make testing easier.
//If you have a need to use these then you're probably doing something wrong.
void MainLoop_Private_SetAtodConversionStatus(int8_t value);

#endif
