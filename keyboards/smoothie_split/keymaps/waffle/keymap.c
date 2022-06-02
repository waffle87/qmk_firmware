#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    KC_VOLU, ___BASE1___, KC_MNXT,
    LINKS,   ___BASE2___, KC_MPLY,
    KC_VOLD, ___BASE3___, KC_MPRV,
    KC_NO, ESCLWR, PSTRSE, KC_NO
  ),
  [_LOWER] = LAYOUT_waffle(
    KC_NO, ___LOWER1___, KC_NO,
    KC_NO, ___LOWER2___, TABLE1,
    KC_NO, ___LOWER3___, TABLE2,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};
