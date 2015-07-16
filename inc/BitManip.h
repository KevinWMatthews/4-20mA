#ifndef BitManip_H_
#define BitManip_H_



//These functions expect bit in the form: 1<<bitNumber
#define IF_BIT(variable, bit) (1 && BITWISE_AND(variable, bit))
#define SET_BIT(variable, bit) ((variable) |= (bit))
#define CLEAR_BIT(variable, bit) ((variable) &= ~(bit))



//These functions expect a bit number (0 to 7 for 8-bit integers)
#define IF_BIT_NUMBER(variable, bitNumber) (1 && BITWISE_AND(1<<(bitNumber), variable))
#define SET_BIT_NUMBER(variable, bitNumber) ((variable) |= (1<<(bitNumber)))
#define CLEAR_BIT_NUMBER(variable, bitNumber) ((variable) &= ~(1<<(bitNumber)))



//These functions can process a bitmask containing multiple bits.
//You must also pass a bitmask containing the bits that are to be affected.
#define IF_BITMASK(expectedBitmask, actualBitmask, bitsToCheck) \
  ( ((bitsToCheck) != 0) && \
    (BITWISE_AND(expectedBitmask, bitsToCheck) == BITWISE_AND(actualBitmask, bitsToCheck)) )

#define SET_BITMASK(variable, newValue, bitsToSet) \
  CLEAR_BITMASK(variable, bitsToSet); \
  ((variable) |= BITWISE_AND(newValue, bitsToSet))

#define CLEAR_BITMASK(variable, bitmask) (variable) &= ~(bitmask)

//Use this when the new value needs to be bit shifted.
//For example, set bits 6 and 7 to 0b11 with
// SET_BITMASK_SHIFT_VALUE(variable, 0b11, 0b11, 6)
#define SET_BITMASK_SHIFT_VALUE(variable, newValue, bitsToSet, shiftForValue) \
  CLEAR_BITMASK(variable, bitsToSet); \
  (variable) |= BITWISE_AND((newValue) << (shiftForValue), bitsToSet)



//Helper macros
#define BITWISE_AND(bitmask1, bitmask2)  ((bitmask1) & (bitmask2))

//This is GCC specific!
//The compiler's return value is 1-indexed.
//I return a 0-indexed value that can be used directly for bitshifting.
//Manually return 0 if the bitmask is 0.
#define RIGHTMOST_BIT_NUMBER(bitmask) ((bitmask) == 0 ? 0 : __builtin_ffs(bitmask) - 1)

#endif
