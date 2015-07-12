#ifndef BitManip_H_
#define BitManip_H_

#define IFBIT(variable, bitNumber) (1 && (1<<(bitNumber) & (variable)))
#define IFBITMASK(expectedBitmask, actualBitmask, bitsToCheck) \
  (((expectedBitmask) & (bitsToCheck)) == ((actualBitmask) & (bitsToCheck)))
#define SBI(variable, bitNumber) ((variable) |= (1<<(bitNumber)))
#define CBI(variable, bitNumber) ((variable) &= ~(1<<(bitNumber)))

#define SBIT(variable, bit) ((variable) |= (bit))
#define CBIT(variable, bit) ((variable) &= ~(bit))


#define CLEAR_BITMASK(variable, bitmask) (variable) &= ~(bitmask)
#define SET_BITMASK_SHIFT(variable, value, bitShift, bitmask) \
  (variable) |= (((value) << (bitShift)) & (bitmask))

#endif
