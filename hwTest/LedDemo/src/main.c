/* In the long run we'll encapsulate the wiring functions in LedDemo,
 * say by adding a toggle function.
 * I just haven't gotten there yet.
 */

#include "LedWiring.h"

int main(void)
{
  LedWiring_Init();

  LedWiring_SetLed(LED_1);
  LedWiring_SetLed(LED_3);
  LedWiring_SetLed(LED_5);
  LedWiring_SetLed(LED_7);

  while (1)
  {
  }
}
