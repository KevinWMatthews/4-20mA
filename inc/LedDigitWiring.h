#ifndef LedDigitWiring_H_
#define LedDigitWiring_H_

/*
 * This file contains the wiring interface.
 * It should NOT contain any hardware specifics.
 * To see the connection to the hardware, refer to the .c file.
 */


//*** Data types ***//
typedef enum
{
  PIN_A = 0,
  PIN_B = 1,
  PIN_C = 2,
  PIN_D = 3,
  PIN_E = 4,
  PIN_F = 5,
  PIN_G = 6,
  PIN_DP =7 ,
  PIN_SELECT = 8
} LedDigitWiring_Pin;


///*** Public functions ***//
void LedDigitWiring_Init(void);
void LedDigitWiring_SetPin(LedDigitWiring_Pin pin);
void LedDigitWiring_ClearPin(LedDigitWiring_Pin pin);

#endif
