#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    ___BASE1___, KC_MPLY,
    ___BASE2___,
    ___BASE3___,
    KC_VOLD, KC_LGUI, LWRSPC, KC_BSPC, CLIPST, KC_VOLU
  ),

  [_LOWER] = LAYOUT_waffle(
    ___LOWER1___, QK_MAKE,
    ___LOWER2___,
    ___LOWER3___,
    KC_MPRV, TABLE1, KC_TRNS, KC_TRNS, TABLE2, KC_MNXT
  )
};
