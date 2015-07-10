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
  PIN_A = 1,
  PIN_B = 2,
  PIN_C = 3,
  PIN_D = 4,
  PIN_E = 5,
  PIN_F = 6,
  PIN_G = 7,
  PIN_DP = 8
} LedDigitWiring_Pin;


///*** Public functions ***//
void LedDigitWiring_HwSetup(void);
void LedDigitWiring_SetPin(LedDigitWiring_Pin pin);
void LedDigitWiring_ClearPin(LedDigitWiring_Pin pin);

#endif
