#include "oled.h"
#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT_smol(
      KC_1, KC_2
  )
};

oled_rotation_t oled_init_user(oled_rotation_t const rotation) {
  return 3;
}

bool oled_task_user(void) {
  render_luna();
  return false;
}
