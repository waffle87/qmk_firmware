#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle_3x6(
    STAR,   ___BASE1___, H_S,
    QMKTD,  ___BASE2___, ROFL,
    DOCSTD, ___BASE3___, RWORD,
    ___BASE4___
  ),
  [_LOWER] = LAYOUT_waffle_3x6(
    KC_NO, ___LOWER1___, KC_NO,
    KC_NO, ___LOWER2___, TABLE1,
    KC_NO, ___LOWER3___, TABLE2,
    ___LOWER4___
  ),
  [_RAISE] = LAYOUT_waffle_3x6(
    KC_NO, ___RAISE1___, KC_NO,
    KC_NO, ___RAISE2___, KC_NO,
    KC_NO, ___RAISE3___, KC_NO,
    ___RAISE4___
  )
};
