#ifndef Mock_LedDigitWiring_H_
#define Mock_LedDigitWiring_H_

#include "DataTypes.h"

void expectHwSetup(void);
void expectPinCall(BOOL setPin, LedDigitWiring_Pin pin);
void expectPinCalls(BOOL pinA, BOOL pinB, BOOL pinC, BOOL pinD, BOOL pinE, BOOL pinF, BOOL pinG);
void expectPinDecimalPointCall(BOOL pinDP);

#endif
