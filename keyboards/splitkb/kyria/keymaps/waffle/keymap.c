#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_stack(
    KC_NO, ALTQ, KC_W, KC_E, KC_R, KC_T,
    KC_NO, SFA,  KC_S, KC_D, KC_F, KC_G,
    KC_NO, CTLZ, KC_X, KC_C, KC_V, KC_B,  QMKTD,  KC_NO,
                 KC_MUTE, KC_LGUI, LOWER, KC_SPC, KC_NO,

                    KC_Y, KC_U,  KC_I,    KC_O,   ALTP,   KC_NO,
                    KC_H, KC_J,  KC_K,    KC_L,   SFCLN,  KC_NO,
    KC_NO, KC_MPLY, KC_N, KC_M,  KC_COMM, KC_DOT, CTLSLH, KC_NO,
    KC_NO, KC_BSPC, RAISE, CLIPST, KC_MPLY
  ),

  [_LOWER] = LAYOUT_stack(
    KC_TRNS, ALT1,   KC_2 ,  KC_3,    KC_4,    KC_5,
    KC_TRNS, SFEXM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC,
    KC_TRNS, CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV,  DEG,     KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                      KC_6,    KC_7,    KC_8,    KC_9,    ALT0,    KC_TRNS,
                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,   KC_TRNS,
    KC_TRNS, DOCSTD,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_RAISE] = LAYOUT_stack(
    KC_TRNS, RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI,
    KC_TRNS, KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,
    KC_TRNS, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,  ROFL,    KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                      KC_NOMODE, KC_SCRIPT, KC_BLOCKS, KC_REGIONAL, QK_BOOT, KC_TRNS,
                      KC_WIDE,   KC_AUSSIE, KC_ZALGO,  KC_SUPER,    EE_CLR,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_F6,     KC_F7,     KC_F8,     KC_F9,       KC_F10,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS
  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
  [_BASE]  = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
  [_LOWER] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
  [_RAISE] = { ENCODER_CCW_CW(C(KC_LEFT), C(KC_RGHT)), ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)) }
};
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
  if (!is_keyboard_master())
    wpm_graph();
  return false;
}
#endif
