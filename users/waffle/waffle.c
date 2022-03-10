// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
#include "g/keymap_combo.h"
userspace_config_t userspace_config;

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LWRSPC:
      return TAPPING_TERM - 30;
    case RSEBSP:
      return TAPPING_TERM - 30;
#ifdef TAP_DANCE_ENABLE
    case GCPTD:
      return TAPPING_TERM - 125;
    case DOCSTD:
    case QMKTD:
      return TAPPING_TERM + 70;
#endif
    default:
      return TAPPING_TERM;
  }
}

__attribute__ ((weak)) void keyboard_post_init_user(void) {
#ifdef RGB_LIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_CYAN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#endif
#ifdef CONSOLE_ENABLE
  debug_keyboard = true;
  debug_enable = true;
  debug_matrix = true;
  debug_mouse = true;
#endif
}

#ifdef TAP_DANCE_ENABLE
#include "secrets.h"
uint8_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  } else return 8;
}

static tap cur_tap_state = {
  .is_press_action = true,
  .state = 0
};

void gclipst_finished(qk_tap_dance_state_t *state, void *user_data) {
  cur_tap_state.state = cur_dance(state);
  switch (cur_tap_state.state) {
    case SINGLE_TAP: register_code16(C(S(KC_V))); break;
    case SINGLE_HOLD: register_code(KC_LGUI); break;
  }
}

void gclipst_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (cur_tap_state.state) {
    case SINGLE_TAP: unregister_code16(C(S(KC_V))); break;
    case SINGLE_HOLD: unregister_code(KC_LGUI); break;
  }
  cur_tap_state.state = 0;
}

void dance_qmk_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code16(C(KC_T));
    send_string(qmkstr);
    tap_code(KC_ENT);
  } else {
    tap_code16(C(KC_T));
    send_string(confstr);
    tap_code(KC_ENT);
  }
}

void dance_doc_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    send_string(docstr);
  } else {
    send_string(drivstr);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [GCLIPST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gclipst_finished, gclipst_reset),
  [QMK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_qmk_finished, NULL),
  [DOCS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_doc_finished, NULL),
};
#endif

#ifdef UNICODEMAP_ENABLE
const uint32_t PROGMEM unicode_map[] = {
  [GENSTAR] = 0x2605,
  [DEGREE] = 0x00B0,
  [HAM_SIK] = 0x262D
};
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    switch (get_highest_layer(layer_state)) {
      case _RAISE:
#if (defined(RGB_LIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE))
        clockwise ? rgblight_increase_sat() : rgblight_decrease_sat();
#endif
        break;
      case _LOWER:
        clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
        break;
      default:
        clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
    }
  } else if (index == 1) {
    switch (get_highest_layer(layer_state)) {
      case _RAISE:
#if (defined(RGB_LIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE))
        clockwise ? rgblight_increase_hue() : rgblight_decrease_hue();
#endif
      break;
      case _LOWER:
#if (defined(POINTING_DEVICE_DRIVER_pimoroni_trackball))
        clockwise ? ball_increase_hue() : ball_decrease_bri();
#endif
        break;
      default:
        clockwise ? tap_code_delay(KC_VOLU, 20) : tap_code_delay(KC_VOLD, 20);
    }
  }
  return false;
}
#endif

#ifdef POINTING_DEVICE_DRIVER_pimoroni_trackball
uint8_t white = 0;
uint8_t red = 255;
uint8_t green = 0;
uint8_t blue = 0;
static bool scrolling = false;

void ball_increase_hue(void){
  if (red != 255 && green != 255 && blue != 255) red = 255;
  if (red == 255 && green < 255 && blue == 0) green += 15;
  else if (green == 255 && blue == 0 && red > 0) red -= 15;
  else if (red == 0 && blue < 255 && green == 255 ) blue += 15;
  else if (blue == 255 && green > 0 && red == 0) green -= 15;
  else if (green == 0 && blue == 255 && red < 255) red += 15;
  else if (green == 0 && blue > 0 && red == 255) blue -= 15;
  pimoroni_trackball_set_rgbw(red, green, blue, white);
}

void ball_decrease_bri(void){
  if (green > 0) green -= 15;
  if (red > 0) red -= 15;
  if (blue > 0) blue -= 15;
  pimoroni_trackball_set_rgbw(red, green, blue, white);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _LOWER:
      scrolling = true;
      pimoroni_trackball_set_cpi(0.1);
      break;
    default:
      if (scrolling) {
        scrolling = false;
        pimoroni_trackball_set_cpi(1);
      }
      break;
  }
  return state;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  if (scrolling) {
    mouse_report.h = mouse_report.x;
    mouse_report.v = -mouse_report.y;
    mouse_report.x = 0;
    mouse_report.y = 0;
  }
  return mouse_report;
}
#endif
