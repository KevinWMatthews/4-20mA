#ifndef BitManip_H_
#define BitManip_H_

#define IF_BIT_NUMBER(variable, bitNumber) (1 && (1<<(bitNumber) & (variable)))
#define IF_BITMASK(expectedBitmask, actualBitmask, bitsToCheck) \
  (((expectedBitmask) & (bitsToCheck)) == ((actualBitmask) & (bitsToCheck)))
#define SET_BIT_NUMBER(variable, bitNumber) ((variable) |= (1<<(bitNumber)))
#define CLEAR_BIT_NUMBER(variable, bitNumber) ((variable) &= ~(1<<(bitNumber)))

#define SET_BIT(variable, bit) ((variable) |= (bit))
#define CLEAR_BIT(variable, bit) ((variable) &= ~(bit))

#endif
