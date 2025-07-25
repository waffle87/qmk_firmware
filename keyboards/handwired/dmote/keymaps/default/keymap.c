/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "keymap_colemak.h"
#include "sendstring_colemak.h"

// Automatic Layer ID:
enum layer_names {
    _QWERTY,   // OS-side Colemak. Default.
    _COLEMAK,  // Keyboard-side Colemak. Portability, emergency.
    _NUMERIC,
};

// Shorthand:
#define LAYER_N MO(_NUMERIC)
#define LAYER_C TG(_COLEMAK)
#define PASTE   LSFT(KC_INS)  // Terminal-compatible paste.
#define SLQ     RALT(KC_9)  // Single left-side quotation mark (in Colemak).
#define SRQ     RALT(KC_0)
#define EMDASH  RALT(LSFT(KC_MINUS))  // Em dash character (in Colemak).
#define BK_LCTL CTL_T(KC_LEFT_BRACKET)
#define BK_RCTL RCTL_T(KC_RIGHT_BRACKET)
// TODO: Mod-tap ALT with a curvilinear brace.
// https://github.com/qmk/qmk_firmware/pull/2055

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_VOLD, KC_VOLU, CM_W,    CM_F,    CM_P,    CM_G,                                     CM_J,    CM_L,    CM_U,    CM_Y,    KC_MPLY, KC_MUTE,
        KC_TAB,  CM_Q,    CM_R,    CM_S,    CM_T,    CM_D,                                     CM_H,    CM_N,    CM_E,    CM_I,    CM_SCLN, KC_BSLS,
        KC_BSPC, CM_A,    CM_X,    CM_C,    CM_V,    CM_B,                                     CM_K,    CM_M,    KC_COMM, KC_DOT,  CM_O,    KC_QUOT,
        SLQ,     CM_Z,    KC_HOME, KC_PGUP, KC_END,                                                     KC_LEFT, KC_UP,   KC_RGHT, KC_SLSH, SRQ,
                                   KC_PGDN,          KC_ENT,  KC_SPC,                 KC_DEL,  KC_ESC,           KC_DOWN,
                                                 SC_LSPO, KC_LGUI, KC_MINS,       KC_EQL,  LAYER_N, SC_RSPC,
                                                     BK_LCTL, KC_LALT,                KC_RALT, BK_RCTL        
    ),

    [_COLEMAK] = LAYOUT(
        _______, _______, KC_W,    KC_F,    KC_P,    KC_G,                                     KC_J,    KC_L,    KC_U,    KC_Y,    _______, _______,
        _______, KC_Q,    KC_R,    KC_S,    KC_T,    KC_D,                                     KC_H,    KC_N,    KC_E,    KC_I,    KC_SCLN, _______,
        _______, KC_A,    KC_X,    KC_C,    KC_V,    KC_B,                                     KC_K,    KC_M,    _______, _______, KC_O,    _______,
        _______, KC_Z,    _______, _______, _______,                                                    _______, _______, _______, _______, _______,
                                   _______,          _______, _______,                _______, _______,          _______,
                                                 _______, _______, _______,       _______, _______, _______,
                                                     _______, _______,                _______, _______
    ),

    [_NUMERIC] = LAYOUT(
        LAYER_C, KC_INS,  KC_F2,   KC_F3,   KC_F4,   KC_F5,                                   KC_F6,   KC_F7,   KC_F8,   KC_F9,   QK_BOOT, KC_WAKE, // *
        KC_F12,  KC_F1,   KC_2,    KC_3,    KC_4,    KC_5,                                    KC_6,    KC_7,    KC_8,    KC_9,    KC_F10,  KC_F11,
        _______, KC_1,    KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                 KC_CIRC, KC_AMPR, KC_ASTR, KC_APP,  KC_0,    PASTE,
        KC_GRV,  KC_EXLM, MS_BTN1, MS_WHLU, MS_BTN2,                                                   MS_LEFT, MS_UP,   MS_RGHT, KC_PSCR, UG_TOGG,
                                   MS_WHLD,          UG_NEXT, _______,               MS_ACL1, MS_ACL2,          MS_DOWN,
                                                 _______, _______, EMDASH,       MS_ACL0, _______, _______,
                                                     _______, _______,               _______, _______
    )
};

// *KC_WAKE: Used in place of KC_SLEP because X11 with i3 on prerelease
//  Debian 10 was seeing duplicate keypress and release events for sleep
//  (regardless of i3 binding), which ruined the function.

/*
The rest is all about lighting control.
The logic here represents a pretty poor compromise solution between the
following concerns:

- Feedback on active modifiers.
- Flexibility: Both sides of the keyboard are interchangeable.
- Regular QMK RBG lighting modes. Specifically, Knight and Xmas.

Currently, the last item suffers, because the first two seem to require
calling a function that implements the RGBLIGHT_SPLIT_SET_CHANGE_HSVS macro,
which most of the rgblight.c functions do not. In particular, functions that
target an individual LED do not do so correctly across the wire, so instead
we let HSV vary without ever targeting LEDs.
*/

// How long to wait between animation steps for "Knight" animation:
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {255, 200, 100};

bool _initialized = false;
bool _leds_dirty = false;

void modal_leds(void) {
    uint8_t mods = get_mods();
    uint16_t hue = 355;  // Rough match to printed case.
    uint8_t saturation = 255;
    uint8_t value = 0;
    if (layer_state_is(_COLEMAK)) { hue -= 50; saturation -= 20; value += 20; }
    if (layer_state_is(_NUMERIC)) { value += 30; }
    if (mods & MOD_MASK_SHIFT) { saturation -= 20; value += 30; }
    if (mods & MOD_MASK_ALT) { hue -= 100; saturation -= 20; value += 30; }
    if (mods & MOD_MASK_CTRL) { hue -= 200; saturation -= 20; value += 30; }
    // rgblight_sethsv_eeprom_helper is not a great API function but it does
    // affect both halves of a split keyboard.
    rgblight_sethsv_eeprom_helper(hue, saturation, value, false);
    _leds_dirty = false;
}

void matrix_scan_user(void) {
    if (_leds_dirty) { modal_leds(); }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!_initialized) {
        // Static lighting is amenable to customization.
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        _initialized = true;
    }
    if (keycode == KC_WAKE) {
        // Turn the lights off before going to sleep.
        rgblight_sethsv_eeprom_helper(0, 0, 0, false);
    } else {
        _leds_dirty = true;
    }
    return true;
}
