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

                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
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
static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
  };
  oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
  if (!is_keyboard_master())
    render_logo();
  return false;
}
#endif
