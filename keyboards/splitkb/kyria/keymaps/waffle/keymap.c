#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_stack(
    KC_TRNS, ALTQ, KC_W, KC_E, KC_R, KC_T,
    KC_TRNS, SFA,  KC_S, KC_D, KC_F, KC_G,
    KC_TRNS, CTLZ, KC_X, KC_C, KC_V, KC_B, QMKTD,  KC_SPC,
                  KC_MUTE, KC_LGUI, LOWER, DOCSTD, KC_SPC,

                   KC_Y, KC_U,  KC_I,    KC_O,   ALTP,   KC_TRNS,
                   KC_H, KC_J,  KC_K,    KC_L,   SFCLN,  KC_TRNS,
    KC_BSPC, DEG,  KC_N, KC_M,  KC_COMM, KC_DOT, CTLSLH, KC_TRNS,
    KC_BSPC, ROFL, RAISE, CLIPST, KC_MPLY
  ),

  [_LOWER] = LAYOUT_stack(
    KC_TRNS, ALT1,   KC_2 ,  KC_3,    KC_4,    KC_5,
    KC_TRNS, SFEXM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC,
    KC_TRNS, CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV,  KC_TRNS, KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                      KC_6,    KC_7,    KC_8,    KC_9,    ALT0,    KC_TRNS,
                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,   KC_TRNS,
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_RAISE] = LAYOUT_stack(
    KC_TRNS, RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI,
    KC_TRNS, KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,
    KC_TRNS, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,  KC_TRNS, KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};
