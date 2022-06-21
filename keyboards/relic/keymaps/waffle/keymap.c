#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_3u (
    ALTQ,  KC_W,    KC_E,   KC_R,   KC_T,   KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_MPLY,
    SFA,   KC_S,    KC_D,   KC_F,   KC_G,   KC_H, KC_J, KC_K,    KC_L,   SFCLN,   
    CTLZ,  KC_X,    KC_C,   KC_V,   KC_B,   KC_N, KC_M, KC_COMM, CTLDOT, CTLSLH,
    KC_VOLD, KC_LGUI, LWRSPC, KC_BSPC, CLIPST, KC_VOLU
  ),

  [_LOWER] = LAYOUT_3u (
    ALT1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    ALT0, QK_MAKE,
    SFEXM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,
    CTLESC, KC_TAB,  KC_NO,   KC_TILD, KC_GRV,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, OUT,
    KC_MPRV, TABLE1, KC_TRNS, DEG, TABLE2, KC_MNXT
  )
};
