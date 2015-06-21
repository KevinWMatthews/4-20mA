#ifndef MainLoop_H_
#define MainLoop_H_

#include "DataTypes.h"

void MainLoop_AtodConversion(void);
int8_t MainLoop_GetAtodConversionStatus(void);

void MainLoop_ReadAtodValue(int16_t * atodValue);

//Included to make testing easier.
//If you have a need to use these then you're probably doing something wrong.
void MainLoop_Private_SetAtodConversionStatus(int8_t value);

#endif
