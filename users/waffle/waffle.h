// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#include "oled.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
void ball_increase_hue(void);
void ball_decrease_bri(void);
bool trackball_is_scrolling(void);
void trackball_set_scrolling(bool scroll);
#endif

typedef struct {
  uint16_t device_cpi;
} kb_config_data_t;

enum layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum tapdances {
  GCLIPST,
  QMK,
  DOCS
};

#ifdef TAP_DANCE_ENABLE
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
void gclipst_finished(qk_tap_dance_state_t *state, void *user_data);
void gclipst_reset(qk_tap_dance_state_t *state, void *user_data);
void dance_qmk_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_doc_finished(qk_tap_dance_state_t *state, void *user_data);
#endif

enum custom_keycodes {
  CP_PSTE = SAFE_RANGE,
  ROFL,
#ifdef UNICODEMAP_ENABLE
  HAP,
  TABLE1,
  TABLE2,
  OUT,
#endif
#ifdef RANDICT
  RWORD,
#endif
  MAKE,
  RST_EEP,
  NEW_SAFE_RANGE
};

#ifdef UNICODEMAP_ENABLE
enum unicodemap_names {
  GENSTAR,
  DEGREE,
  HAM_SIK
};
#endif

//---layers---
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define LWRSPC LT(_LOWER, KC_SPC)
#define RSEBSP LT(_RAISE, KC_BSPC)
//---general---
#define SFA SFT_T(KC_A)
#define SFCLN RSFT_T(KC_SCLN)
#define SFEXM MT(MOD_LSFT, KC_F23)
#define SFPRN MT(MOD_RSFT, KC_F24)
#define ALTQ ALT_T(KC_Q)
#define ALTP ALT_T(KC_P)
#define ALT1 ALT_T(KC_1)
#define ALT0 ALT_T(KC_0)
#define CTLZ CTL_T(KC_Z)
#define CTLESC CTL_T(KC_ESC)
#define CTLSLH CTL_T(KC_SLSH)
#define CTLDOT CTL_T(KC_DOT)
#define CTLRGHT CTL_T(KC_RIGHT)
#define CLIPST C(S(KC_V))
//---tapdance---
#define DOCSTD TD(DOCS)
#define QMKTD TD(QMK)
#define GCPTD TD(GCLIPST)
//---unicode---
#define DEG X(DEGREE)
#define H_S X(HAM_SIK)
#define STAR X(GENSTAR)

#define LAYOUT_waffle(...)   LAYOUT_split_3x6_3(__VA_ARGS__)
#define _BASE1 STAR,    ALTQ, KC_W, KC_E, KC_R, KC_T,          KC_Y, KC_U, KC_I,    KC_O,   ALTP,   ROFL,
#define _BASE2 QMKTD,   SFA,  KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K,    KC_L,   SFCLN,  DEG,
#define _BASE3 CP_PSTE, CTLZ, KC_X, KC_C, KC_V, KC_B,          KC_N, KC_M, KC_COMM, KC_DOT, CTLSLH, RWORD,
#define _BASE4                     KC_LGUI, LOWER, KC_SPC, KC_BSPC, RSEBSP, CLIPST

#define _LOWER1 HAP,    ALT1,   KC_2,   KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    ALT0,    MAKE,
#define _LOWER2 DOCSTD, SFEXM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,   TABLE1,
#define _LOWER3 OUT,    CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL, TABLE2,
#define _LOWER4                              KC_TRNS, KC_TRNS, KC_SPC, KC_VOLU, KC_TRNS, KC_TRNS

#define _RAISE1 RGB_TOG,  RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_TRNS,       KC_MPRV, KC_MPLY, KC_MNXT, CK_TOGG, CK_RST,  QK_BOOT,
#define _RAISE2 RGB_MOD,  RGB_HUD, RGB_SAD, RGB_VAD, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR,
#define _RAISE3 RGB_RMOD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
#define _RAISE4                               KC_TRNS, KC_TRNS, KC_VOLD, KC_BSPC, KC_TRNS, KC_TRNS

#define _ADJUST1 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
#define _ADJUST2 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
#define _ADJUST3 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
#define _ADJUST4                                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
