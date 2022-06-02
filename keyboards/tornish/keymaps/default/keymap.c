#include QMK_KEYBOARD_H

enum macros {
  DAY = SAFE_RANGE,
  CLEAR,
  GIVE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    DAY,   KC_Q, KC_W, KC_E, KC_R, KC_T,
    CLEAR, KC_A, KC_S, KC_D, KC_F, KC_G,
    GIVE,  KC_Z, KC_X, KC_C, KC_V, KC_B,
    KC_ESC, MO(1), KC_SPC, KC_NO
  ),
  [1] = LAYOUT(
    KC_NO, KC_1,  KC_2,  KC_3,  KC_4,  KC_5,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    QK_BOOT, KC_NO, KC_TRNS, KC_NO
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DAY:
      if (record->event.pressed) {
        tap_code(KC_SLSH);
        wait_ms(500);
        SEND_STRING("time set day" SS_TAP(X_ENT));
      }
      break;
    case CLEAR:
      if (record->event.pressed) {
        tap_code(KC_SLSH);
        wait_ms(500);
        SEND_STRING("weather clear" SS_TAP(X_ENT));
      }
      break;
    case GIVE:
      if (record->event.pressed) {
        tap_code(KC_SLSH);
        wait_ms(500);
        SEND_STRING("give box666 " SS_TAP(X_ENT));
      }
      break;
  }
  return true;
}
