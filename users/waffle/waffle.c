// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
#include "combos.h"

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

__attribute__ ((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__ ((weak)) void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
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
td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1)
    if (state->interrupted || !state->pressed)
      return SINGLE_TAP;
    else
      return SINGLE_HOLD;
  else if (state->count == 2)
      return DOUBLE_TAP;
  else
   return NONE;
}

static td_tap_t xtap_state = {
  .is_press_action = true,
  .state = NONE
};

void gclipst_finished(qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code16(C(S(KC_V))); break;
    case SINGLE_HOLD: register_code(KC_LGUI); break;
    case DOUBLE_TAP:
    case NONE:
      break;
  }
}

void gclipst_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code16(C(S(KC_V))); break;
    case SINGLE_HOLD: unregister_code(KC_LGUI); break;
    case DOUBLE_TAP:
    case NONE:
      break;
  }
  xtap_state.state = NONE;
}

void qmk_dance(qk_tap_dance_state_t *state, void *user_data) {
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

void doc_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1)
    send_string(docstr);
  else
    send_string(drivstr);
}

void dash_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1)
    tap_code(KC_MINS);
  else
    register_unicode(0x2014);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [GCLIPST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gclipst_finished, gclipst_reset),
  [QMK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, qmk_dance, NULL),
  [DOCS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, doc_dance, NULL),
  [EM_DASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dash_dance, NULL)
};
#endif

#if !defined (ENCODER_MAP_ENABLE) && defined (ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    switch (get_highest_layer(layer_state)) {
      case _LOWER:
#if defined (RGBLIGHT_ENABLE) || defined (RGB_MATRIX_ENABLE)
        clockwise ? rgblight_increase_hue() : rgblight_decrease_hue();
#endif
        break;
      default:
        clockwise ? tap_code_delay(KC_VOLU, 20) : tap_code_delay(KC_VOLD, 20);
    }
  } else if (index == 1) {
    switch (get_highest_layer(layer_state)) {
      case _LOWER:
#if defined (RGBLIGHT_ENABLE) || defined (RGB_MATRIX_ENABLE)
        clockwise ? rgblight_increase_sat() : rgblight_decrease_sat();
#endif
      break;
      default:
        clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
    }
  }
  return false;
}
#endif

#ifdef POINTING_DEVICE_DRIVER_pimoroni_trackball
uint8_t red = 255, green = 0, blue = 0;

void trackball_hue(void) {
  if (red != 255 && green != 255 && blue != 255) red = 255;
  if (red == 255 && green < 255 && blue == 0) green += 15;
  else if (green == 255 && blue == 0 && red > 0) red -= 15;
  else if (red == 0 && blue < 255 && green == 255 ) blue += 15;
  else if (blue == 255 && green > 0 && red == 0) green -= 15;
  else if (green == 0 && blue == 255 && red < 255) red += 15;
  else if (green == 0 && blue > 0 && red == 255) blue -= 15;
  pimoroni_trackball_set_rgbw(red, green, blue, 0);
}
#endif

#ifdef POINTING_DEVICE_ENABLE
static bool scrolling = false;
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _LOWER:
      scrolling = true;
      pointing_device_set_cpi(64);
#ifdef POINTING_DEVICE_DRIVER_pimoroni_trackball
      pimoroni_trackball_set_cpi(0.1);
#endif
      break;
    default:
      if (scrolling) {
        scrolling = false;
        pointing_device_set_cpi(1024);
#ifdef POINTING_DEVICE_DRIVER_pimoroni_trackball
        pimoroni_trackball_set_cpi(1);
#endif
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
