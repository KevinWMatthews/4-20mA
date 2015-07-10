#ifndef LedDigitWiring_H_
#define LedDigitWiring_H_



//This hardware-dependent module is inteded to by used by the LedDigit module only.
//It is an abstraction layer to keep LedDigit from having direct hardware dependencies.
//It is NOT designed to be used directly by the user.
//To use LedDigits, refer to LedDigit.h
//In other words, unless LedDigit broken, GO AWAY!



//******************//
//*** Data types ***//
//******************//
typedef enum
{
  PIN_A  = 1,
  PIN_B  = 2,
  PIN_C  = 3,
  PIN_D  = 4,
  PIN_E  = 5,
  PIN_F  = 6,
  PIN_G  = 7,
  PIN_DP = 8
} LedDigitWiring_Pin;



//************************//
//*** Public Functions ***//
//************************//
void LedDigitWiring_HwSetup(void);
void LedDigitWiring_TurnSegmentOn(LedDigitWiring_Pin pin);
void LedDigitWiring_TurnSegmentOff(LedDigitWiring_Pin pin);



#endif
