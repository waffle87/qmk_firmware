// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
#include "oled.h"
#endif

#ifdef RAW_ENABLE
#pragma message "check other device's vid/pid"
typedef struct {
  uint8_t cpu_temp;
  uint8_t hour;
  uint8_t min;
} user_config;
user_config user_state;
#endif

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

enum layers {
  _BASE,
  _ADJUST,
  _LOWER,
  _RAISE
};

enum tapdances {
  QMK_LINKS,
  EM_DASH,
  CBRKT,
  BRKT,
  BSLS_PIPE,
  DEG_0,
  PLY_NXT_PRV,
  CLIPST_RAISE
};


enum custom_keycodes {
  UPDIR = SAFE_RANGE,
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
  NEW_SAFE_RANGE
};

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

//---home row mods---
#define A_ALT LALT_T(KC_A)
#define S_GUI LGUI_T(KC_S)
#define D_CTL LCTL_T(KC_D)
#define F_SFT LSFT_T(KC_F)
#define J_SFT RSFT_T(KC_J)
#define K_CTL RCTL_T(KC_K)
#define L_GUI RGUI_T(KC_L)
#define CLN_ALT RALT_T(KC_SCLN)
#define EXM_ALT LALT_T(KC_EXLM)
#define AT_GUI LGUI_T(KC_AT)
#define HASH_CTL LCTL_T(KC_HASH)
#define DLR_SFT LSFT_T(KC_DLR)
#define AMPR_SFT RSFT_T(KC_AMPR)
#define ASTR_CTL RCTL_T(KC_ASTR)
#define LPRN_GUI RGUI_T(KC_LPRN)
#define RPRN_ALT RALT_T(KC_RPRN)
//---tapdance---
#define DEG0 TD(DEG_0)
#define LINKS TD(QMK_LINKS)
#define PNP TD(PLY_NXT_PRV)
#define PSTRSE TD(CLIPST_RAISE)
//---misc---
#define H_S UC(0x262D) //☭
#define STAR UC(0x2605) //★
#define ESCLWR LT(_LOWER, KC_ESC)
#define LWRSPC LT(_LOWER, KC_SPC)
#define RSEBSP LT(_RAISE, KC_BSPC)

#define ___BASE1___ KC_Q,  KC_W,  KC_E,  KC_R,  KC_T, KC_Y, KC_U,  KC_I,    KC_O,   KC_P
#define ___BASE2___ A_ALT, S_GUI, D_CTL, F_SFT, KC_G, KC_H, J_SFT, K_CTL,   L_GUI,  CLN_ALT
#define ___BASE3___ KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH
#define ___BASE4___ UPDIR, ESCLWR, KC_SPC, KC_BSPC, PSTRSE, PNP

#define ___LOWER1___ KC_1,    KC_2,   KC_3,     KC_4,    KC_5,    KC_6,    KC_7,     KC_8,     KC_9,     DEG0
#define ___LOWER2___ EXM_ALT, AT_GUI, HASH_CTL, DLR_SFT, KC_PERC, KC_CIRC, AMPR_SFT, ASTR_CTL, LPRN_GUI, RPRN_ALT
#define ___LOWER3___ KC_VOLD, KC_TAB, KC_CAPS,  KC_TILD, KC_GRV,  KC_LEFT, KC_DOWN,  KC_UP,    KC_RGHT,  KC_VOLU
#define ___LOWER4___ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

#define ___RAISE1___ RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, KC_NOMODE, KC_SCRIPT, KC_BLOCKS, KC_REGIONAL, QK_MAKE
#define ___RAISE2___ CK_TOGG, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_WIDE,   KC_AUSSIE, KC_ZALGO,  KC_SUPER,    QK_BOOT
#define ___RAISE3___ KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7,     KC_F8,     KC_F9,       KC_F10
#define ___RAISE4___ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

#define LAYOUT_waffle_3x6(...) LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_waffle_3x5(...) LAYOUT_split_3x5_3(__VA_ARGS__)
#define LAYOUT_waffle(...)     LAYOUT(__VA_ARGS__)
