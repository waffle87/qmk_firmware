/* Copyright 2021 Hydrogen BD <support@hgenbd.com>
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
 
#include "quantum.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    const layer_state_t curr_layer = get_highest_layer(layer_state);
    if(curr_layer == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if(curr_layer == 1) {
        if (clockwise) {
            tap_code(MS_WHLD);
        } else {
            tap_code(MS_WHLU);
        }
    }
    else if(curr_layer == 2) {
        if (clockwise) {
            tap_code16(C(MS_WHLU));
        } else {
            tap_code16(C(MS_WHLD));
        }
    }
    else {
        if (clockwise) {
            tap_code(KC_BRIU);
        } else {
            tap_code(KC_BRID);
        }
    }
    return false;
}
#endif