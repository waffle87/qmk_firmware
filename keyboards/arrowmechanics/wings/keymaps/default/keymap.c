// Copyright 2024 Filip Strzałka (@philvec)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    BASE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_VOLU, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,                            KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_EQL,   KC_PSCR,  KC_DEL,
        KC_VOLD, KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,   RM_NEXT,        MS_BTN1,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,       KC_BSPC,
        KC_MPLY,       KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,   C(KC_C),        C(KC_V),  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_MNXT,      KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,     KC_G,   C(KC_Z),        C(KC_Y),  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,       KC_ENT,
        KC_MPRV,      KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,   KC_ENT,         KC_ENT,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_UP,    KC_HOME,
        KC_LCTL, KC_NO,   KC_NO,            KC_LCTL, KC_LCMD, KC_LALT,      KC_SPC,                  KC_SPC,       KC_RALT, KC_RCMD, KC_RCTL,          KC_LEFT,  KC_DOWN,  KC_RGHT
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] =   { ENCODER_CCW_CW(RM_HUEU, RM_HUED), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
};
#endif
