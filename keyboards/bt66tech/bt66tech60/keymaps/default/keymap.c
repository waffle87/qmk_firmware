/* Copyright 2020 bt66tech
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
    _FN1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
[_BASE] = LAYOUT_60_ansi(
    QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                 KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC, 
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,   		KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS, 
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,                 KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,  
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,                 	 KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT, 
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                          KC_RALT, KC_RGUI, KC_RCTL,  MO(_FN)
  ),

  [_FN] = LAYOUT_60_ansi(
    	  KC_GRV,      KC_F1,       KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,    KC_F7,   KC_F8,    KC_F9,     KC_F10,  KC_F11,  KC_F12, 	KC_DEL, 
    MS_ACL0, MS_BTN1,    MS_UP,   MS_BTN2, 	 _______,    _______, 	 _______,  _______, _______,  _______, KC_PSCR, _______, _______, _______, 
    MS_ACL1, MS_LEFT,  MS_DOWN,MS_RGHT,  	 _______,    _______,	 _______,  _______, _______,  _______,    _______, _______,          _______, 
    MS_ACL2,    _______,     _______,    _______,    _______,    _______,    _______,  _______, _______,  _______,              KC_UP,          MO(_FN1), 
    	 _______,    _______,     _______,                                       _______,                                 KC_LEFT, KC_DOWN, KC_RGHT, _______
  ),

[_FN1] = LAYOUT_60_ansi(
    BL_TOGG, BL_STEP,   BL_ON,   BL_OFF,   BL_UP,    BL_DOWN,  BL_BRTG,   _______,   _______,   _______,   _______,  BL_DOWN, BL_UP,    _______, 
     _______, _______,  _______,   _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, 
     _______,  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______, _______, _______,          _______, 
     _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, 
    _______,  _______, _______,                            _______,                            _______,  _______, _______, _______
  )

};
