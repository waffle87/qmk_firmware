// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
#include "oled.h"
#endif

void trackball_hue(void);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

enum layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

#ifdef TAP_DANCE_ENABLE
enum tapdances {
  ALTDEG0,
  QMK,
  DOCS,
  EM_DASH
};

typedef enum {
  NONE,
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_TAP
} td_state_t;

typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state);
void alt_deg_0(qk_tap_dance_state_t *state, void *user_data);
void qmk_dance(qk_tap_dance_state_t *state, void *user_data);
void doc_dance(qk_tap_dance_state_t *state, void *user_data);
void dash_dance(qk_tap_dance_state_t *state, void *user_data);
#endif

#ifdef UNICODE_COMMON_ENABLE
bool process_record_unicode(uint16_t keycode, keyrecord_t *record);

enum unicode_mode {
  NOMODE,
  WIDE,
  SCRIPT,
  BLOCKS,
  REGIONAL,
  AUSSIE,
  ZALGO,
  SUPER
};
#endif

enum custom_keycodes {
  CP_PSTE = SAFE_RANGE,
  ROFL,
  TABLE1,
  TABLE2,
  KC_NOMODE,
  KC_WIDE,
  KC_SCRIPT,
  KC_BLOCKS,
  KC_REGIONAL,
  KC_AUSSIE,
  KC_ZALGO,
  KC_SUPER,
  RWORD,
  RST_EEP,
  NEW_SAFE_RANGE
};

//---layers---
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define LWRSPC LT(_LOWER, KC_SPC)
#define RSEBSP LT(_RAISE, KC_BSPC)
//---general---
#define SFA LSFT_T(KC_A)
#define SFCLN RSFT_T(KC_SCLN)
#define SFEXM LSFT_T(KC_F23)
#define SFPRN RSFT_T(KC_F24)
#define ALTQ LALT_T(KC_Q)
#define ALTP RALT_T(KC_P)
#define ALT1 LALT_T(KC_1)
#define CTLZ LCTL_T(KC_Z)
#define CTLESC LCTL_T(KC_ESC)
#define CTLSLH RCTL_T(KC_SLSH)
#define CTLDOT RCTL_T(KC_DOT)
#define CTLRGHT RCTL_T(KC_RIGHT)
#define CLIPST C(S(KC_V))
//---tapdance---
#define ALT0 TD(ALTDEG0)
#define DOCSTD TD(DOCS)
#define QMKTD TD(QMK)
//---unicode---
#define H_S UC(0x262D)
#define STAR UC(0x2605)

#define ___BASE1___ ALTQ, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   ALTP
#define ___BASE2___ SFA,  KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   SFCLN
#define ___BASE3___ CTLZ, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, CTLSLH
#define ___BASE4___ KC_LGUI, LOWER, KC_SPC, KC_BSPC, RAISE, CLIPST

#define ___LOWER1___ ALT1,   KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    ALT0
#define ___LOWER2___ SFEXM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN
#define ___LOWER3___ CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL
#define ___LOWER4___ KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_TRNS, KC_MNXT

#define ___RAISE1___ RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, KC_NOMODE, KC_SCRIPT, KC_BLOCKS, KC_REGIONAL, QK_MAKE
#define ___RAISE2___ CK_TOGG, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_WIDE,   KC_AUSSIE, KC_ZALGO,  KC_SUPER,    QK_BOOT
#define ___RAISE3___ KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7,     KC_F8,     KC_F9,       KC_F10
#define ___RAISE4___ KC_MPRV, KC_TRNS, KC_VOLD, KC_TRNS, KC_TRNS, KC_TRNS

#define LAYOUT_waffle_3x6(...) LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_waffle_3x5(...) LAYOUT_split_3x5_3(__VA_ARGS__)
#define LAYOUT_waffle(...)     LAYOUT(__VA_ARGS__)
