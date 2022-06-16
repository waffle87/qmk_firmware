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
  if (state->count == 1)
    send_string(docstr);
  else
    send_string(drivstr);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [GCLIPST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gclipst_finished, gclipst_reset),
  [QMK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_qmk_finished, NULL),
  [DOCS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_doc_finished, NULL)
};
#endif

#ifdef UNICODEMAP_ENABLE
const uint32_t PROGMEM unicode_map[] = {
  [GENSTAR] = 0x2605,
  [DEGREE] = 0x00B0,
  [HAM_SIK] = 0x262D
};
#endif

#ifdef POINTING_DEVICE_DRIVER_pimoroni_trackball
uint8_t white = 0;
uint8_t red = 255;
uint8_t green = 0;
uint8_t blue = 0;

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
