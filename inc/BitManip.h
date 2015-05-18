#ifndef BitManip_H_
#define BitManip_H_

#define IFBIT(variable, bitNumber) (1 && (1<<(bitNumber) & (variable)))
#define IFBITMASK(variable, actualBitmask, bitsToCheck) \
  (((variable) & (bitsToCheck)) == ((actualBitmask) & (bitsToCheck)))
#define SBI(variable, bitNumber) ((variable) |= (1<<(bitNumber)))
#define CBI(variable, bitNumber) ((variable) &= ~(1<<(bitNumber)))

#endif
