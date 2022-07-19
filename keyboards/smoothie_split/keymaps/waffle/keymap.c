#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    KC_VOLU, ___BASE1___, KC_MNXT,
    QMKTD,   ___BASE2___, KC_MPLY,
    KC_VOLD, ___BASE3___, KC_MPRV,
    KC_LGUI, LWRSPC, KC_BSPC, CLIPST
  ),
  [_LOWER] = LAYOUT_waffle(
    KC_NO, ___LOWER1___, KC_NO,
    KC_NO, ___LOWER2___, TABLE1,
    KC_NO, ___LOWER3___, TABLE2,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};
