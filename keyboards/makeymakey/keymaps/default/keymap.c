/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

// clang-format off
/*
 *     ,-----------------------------------------------------.
 *     |                                                     |
 *     |          (UP)                                       |
 * MSU |           ^                   .-""-.      .-""-.    | W
 * MSD |           |                  /      \    /      \   | A
 * MSL | (LEFT)<== O ==> (RIGHT)     ;        ;  ;        ;  | S
 * MSR |           |                  \      /    \      /   | D
 * MB1 |           v                   '-..-'      '-..-'    | F
 * MB2 |         (DOWN)               (SPACE)    (RGHT CLK)  | G
 *     |                                                     |
 *     \-----------------------------------------------------/
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_UP,   KC_DOWN, KC_LEFT, KC_RGHT, KC_SPC,  MS_BTN1,
        KC_W,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        MS_UP,   MS_DOWN, MS_LEFT, MS_RGHT, MS_BTN1, MS_BTN2
    )
};

// clang-format on
