// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,     KC_F10,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,   KC_F16,    KC_F17,
        KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,   KC_F23,    KC_F24 
    )
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif
