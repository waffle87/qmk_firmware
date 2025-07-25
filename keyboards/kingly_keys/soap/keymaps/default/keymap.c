/* Copyright 2019 Garret G. (TheRoyalSweatshirt)
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

#define BASE 0
#define FN 1
#define XXX KC_NO
#define KC_TR KC_TRANSPARENT
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE
   * ,----------------------------------------.
   * |  DEL  |   UP  | ENTER |       |  RGB   |
   * |-------+-------+-------+-------+--------|
   * | LEFT  | DOWN  | RIGHT |       |   FN   |
   * `----------------------------------------'
   */
  	[BASE] = LAYOUT(
    KC_DEL,  KC_UP,   KC_ENT,           UG_NEXT,
    KC_LEFT, KC_DOWN, KC_RIGHT,         MO(1)
  ),

    /* FN
   * ,----------------------------------------.
   * |  HU+  |  Br+  |  Sat+ |       |        |
   * |-------+-------+-------+-------+--------|
   * |  HU-  |  Br-  |  Sat- |       |        |
   * `----------------------------------------'
   */
  	[FN] = LAYOUT(
    UG_HUEU, UG_VALU, UG_SATU,         KC_TR,
    UG_HUED, UG_VALD, UG_SATD,         KC_TR
  )
};

    /*      Rotary Encoder Settings:                     */
    /*       - Current Value = Horizontal Scrolling      */

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(MS_WHLL);
        } else {
            tap_code(MS_WHLR);
        }
    }
    return true;
}
