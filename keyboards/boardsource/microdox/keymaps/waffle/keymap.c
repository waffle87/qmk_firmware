#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x5_3(
    ALTQ, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I,    KC_O,   ALTP,
    SFA,  KC_S, KC_D, KC_F, KC_G,         KC_H, KC_J, KC_K,    KC_L,   SFCLN,
    CTLZ, KC_X, KC_C, KC_V, KC_B,         KC_N, KC_M, KC_COMM, KC_DOT, CTLSLH,
            KC_LGUI, LOWER, KC_SPC,       KC_BSPC, RAISE, CLIPST
  ),

  [_LOWER] = LAYOUT_split_3x5_3(
    ALT1,   KC_2,   KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    ALT0,
    SFEXM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,
    CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL,
                    KC_TRNS, KC_TRNS, KC_TRNS,         KC_VOLU, KC_TRNS, KC_MNXT
  ),

  [_RAISE] = LAYOUT_split_3x5_3(
    RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
    KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR,
    KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                       KC_MPRV, KC_TRNS, KC_VOLD,         KC_TRNS, KC_TRNS, KC_TRNS
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return 0;
  else
   return 2;
  return rotation;
}

bool oled_task_user(void) {
  if (is_keyboard_master())
    render_layer_anim();
  else
    render_wpm(0);
  return false;
}
#endif
