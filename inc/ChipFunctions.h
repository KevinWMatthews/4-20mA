#ifndef ChipFunctions_H
#define ChipFunctions_H


//Specific bit manipulations that are general to the chip
//but specific to the Atmel Tiny26
void ChipFunctions_EnableGlobalInterrupts(void);
void ChipFunctions_DisableGlobalInterrupts(void);

typedef enum
{
  CF_CPU_PRESCALE_FACTOR_1   = 0b0000,
  CF_CPU_PRESCALE_FACTOR_8   = 0b0011,  //Factory default
  CF_CPU_PRESCALE_FACTOR_128 = 0b0111,
  CF_CPU_PRESCALE_FACTOR_256 = 0b1000
} Cf_CpuPrescaleFactor;
void ChipFunctions_SetCpuPrescaler(Cf_CpuPrescaleFactor);



#endif
