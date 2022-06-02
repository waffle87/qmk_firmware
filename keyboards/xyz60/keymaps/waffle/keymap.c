#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    PNP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC,
    _______, ___BASE1___, _______, _______, _______,
    LINKS,___BASE2___, _______, _______,
    _______, ___BASE3___, _______, _______,
    KC_VOLD, KC_ESC, KC_ESC, LWRSPC, C(S(KC_V)), C(S(KC_V)), C(S(KC_V)), KC_VOLU
  ),
  [_LOWER] = LAYOUT_waffle(
    QK_BOOT, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_MAKE,
    _______, ___LOWER1___, _______, _______, _______,
    _______, ___LOWER2___, _______, _______,
    _______, ___LOWER3___, _______, _______,
    KC_MPRV, _______, _______, _______, _______, _______, _______, KC_MNXT
  )
};
