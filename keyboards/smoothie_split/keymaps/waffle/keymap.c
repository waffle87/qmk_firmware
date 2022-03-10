#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    STAR,    ALTQ, KC_W, KC_E, KC_R, KC_T,          KC_Y, KC_U, KC_I, KC_O, ALTP, KC_MNXT,
    QMKTD,   SFA,  KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K, KC_L, SFCLN, KC_MPLY,
    CP_PSTE, CTLZ, KC_X, KC_C, KC_V, KC_B,          KC_N, KC_M, KC_COMM, KC_DOT, CTLSLH, KC_MPRV,
                          KC_LGUI, LWRSPC,          RSEBSP, CLIPST
  ),
  [_LOWER] = LAYOUT(
    HAP,    ALT1,   KC_2,   KC_3,    KC_4,    KC_5,        KC_6, KC_7, KC_8, KC_9, ALT0, MAKE,
    DOCSTD, SFEXM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,   TABLE1,
    OUT,    CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL, TABLE2,
                                     KC_LGUI, KC_TRNS,     KC_VOLU, KC_PGUP
  ),
  [_RAISE] = LAYOUT(
    KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS,       KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, RESET,
    KC_INS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PIPE,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_END, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
                                    KC_PGDN,   KC_VOLD,       KC_TRNS, KC_TRNS
  )
};
