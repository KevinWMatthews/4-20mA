#ifndef LedWiring_H_
#define LedWiring_H_

#include <avr/io.h>
#include "DataTypes.h"

#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7


/* This file encapsulates the hardware dependencies of LedDemo.
 * LedDemo_Wiring will depend directly on a particular chip and its manufacturer-provided header file.
 * This header will be found by the embedded compiler during production builds.
 * For test builds, direct gcc to a dummy header file that mocks/copies the special memory register defines.
 * This dummy header will contain variables that are used in lieu of the real ones; these can be used for testing.
 *
 * Some TDD sources recommend an alternative method, instead passing memory addresses into the LedDemo
 * at a high level (in the Init function). This method is useful for memory-mapped registers that are
 * accessed as a whilebut proves to be cumbersome and ineffient when bits are acessed individually.
 * This is an attempt at reconciling hardware independence with testability.
 */


#define LED_1 (1<<PA0)
#define LED_2 (1<<PA1)
#define LED_3 (1<<PA2)
#define LED_4 (1<<PA3)
#define LED_5 (1<<PA4)
#define LED_6 (1<<PA5)
#define LED_7 (1<<PA6)
#define LED_8 (1<<PA7)

void LedWiring_Init(void);

//Choose from the list defined above
void LedWiring_SetLed(int8_t ledNumber);
void LedWiring_ClearLed(int8_t ledNumber);

#endif
