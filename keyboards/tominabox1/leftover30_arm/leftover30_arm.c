#include "leftover30_arm.h"

void keyboard_pre_init_kb(void) {
  setPinOutput(B10);
  setPinOutput(B11);
}
