#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#include "keymap_german.h"

#include "keymap_nordic.h"



enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ergodox(KC_EQUAL,KC_1,KC_2,KC_3,KC_4,KC_5,LCTL(KC_MINUS),KC_DELETE,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_LBRC,KC_BSPC,KC_A,KC_S,KC_D,KC_F,KC_G,SC_LSPO,CTL_T(KC_Z),KC_X,KC_C,KC_V,KC_B,HYPR_T(KC_NO),LT(1,KC_GRAVE),KC_QUOTE,LALT(KC_LSFT),KC_LEFT,KC_RIGHT,ALT_T(KC_APPLICATION),KC_LGUI,KC_HOME,KC_SPACE,KC_UNDS,KC_END,LCTL(KC_EQUAL),KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_RBRC,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLS,KC_H,ALT_T(KC_J),KC_K,KC_L,LT(2,KC_SCLN),GUI_T(KC_QUOTE),MEH_T(KC_NO),KC_N,KC_M,KC_COMMA,KC_DOT,CTL_T(KC_SLASH),SC_RSPC,KC_UP,KC_DOWN,KC_LBRC,KC_RBRC,TT(1),KC_LALT,CTL_T(KC_ESCAPE),KC_PGUP,KC_PGDN,LT(1,KC_TAB),KC_ENTER),

  [1] = LAYOUT_ergodox(KC_TRANSPARENT,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LCTL(KC_W),KC_LBRC,KC_RBRC,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LCTL(KC_PGUP),LCTL(KC_PGDN),UG_NEXT,KC_TRANSPARENT,KC_TRANSPARENT,UG_VALD,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_F12,KC_AMPR,KC_UNDS,KC_MINUS,KC_SCLN,KC_PLUS,KC_TRANSPARENT,KC_TRANSPARENT,KC_PIPE,KC_AT,KC_EQUAL,KC_PERC,KC_BSLS,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,UG_TOGG,RGB_SLD,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,UG_HUEU),

  [2] = LAYOUT_ergodox(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,MS_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,MS_LEFT,MS_DOWN,MS_RGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,MS_BTN1,MS_BTN2,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_WWW_BACK),

};

void matrix_init_user(void) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_COLOR_LAYER_0)
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
#ifdef RGBLIGHT_ENABLE
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
#endif

  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 0:
        #ifdef RGBLIGHT_ENABLE
          #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
          #else
          rgblight_init();
          #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_COLOR_LAYER_1)
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_COLOR_LAYER_2)
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_COLOR_LAYER_3)
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_COLOR_LAYER_4)
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_COLOR_LAYER_5)
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_COLOR_LAYER_6)
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_COLOR_LAYER_7)
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

    return state;
};
