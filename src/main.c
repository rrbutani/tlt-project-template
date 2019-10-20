
#include <stdbool.h>
#include <stdint.h>

#include "tm4c123gh6pm.h"

#define BUTTON_PRESS_THRESHOLD 500000

// Make PF2 an output, enable digital I/O, ensure alt. functions off
void portf_init(void) {
  SYSCTL_RCGCGPIO_R |= 0x20;  // 1) activate clock for Port F
  while ((SYSCTL_PRGPIO_R & 0x20) == 0) {
  };                                 // allow time for clock to start
                                     // 2) no need to unlock PF2, PF4
  GPIO_PORTF_PCTL_R &= ~0x000F0F00;  // 3) regular GPIO
  GPIO_PORTF_AMSEL_R &= ~0x14;       // 4) disable analog function on PF1-4
  GPIO_PORTF_PUR_R |= 0x10;          // 5) pullup for PF4
  GPIO_PORTF_DIR_R |= 0x0E;          // 5) set direction to output
  GPIO_PORTF_AFSEL_R &= ~0x1E;       // 6) regular port function
  GPIO_PORTF_DEN_R |= 0x1E;          // 7) enable digital port
}

void toggle_red() { GPIO_PORTF_DATA_R ^= 0x02; }

void toggle_blue() { GPIO_PORTF_DATA_R ^= 0x04; }

void toggle_green() { GPIO_PORTF_DATA_R ^= 0x08; }

void wait_for_press() {
  uint32_t count = 0;

  while (true) {
    if (!(GPIO_PORTF_DATA_R & 0x10)) {
      count++;
    } else {
      count = 0;
    }

    if (count > BUTTON_PRESS_THRESHOLD) {
      return;
    }
  }
}

int main() {
  portf_init();

  uint8_t count = 0;
  toggle_green();

  while (true) {
    wait_for_press();
    if (count % 4) {
      toggle_blue();
    } else if (count % 2) {
      toggle_green();
    } else {
      toggle_red();
    }

    count++;
  }
}
