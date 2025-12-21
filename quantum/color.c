/* Copyright 2017 Jason Williams
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

#include <lib/lib8tion/lib8tion.h>
#include "color.h"
#include "led_tables.h"
#include "progmem.h"
#include "util.h"

rgb_t hsv_to_rgb_impl(hsv_t hsv, bool use_cie) {
    rgb_t    rgb;
    uint8_t  region, remainder;
    uint16_t h, s, v;

    if (hsv.s == 0) {
#ifdef USE_CIE1931_CURVE
        if (use_cie) {
            rgb.r = rgb.g = rgb.b = pgm_read_byte(&CIE1931_CURVE[hsv.v]);
        } else {
            rgb.r = hsv.v;
            rgb.g = hsv.v;
            rgb.b = hsv.v;
        }
#else
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
#endif
        return rgb;
    }

    h = hsv.h;
    s = hsv.s;
    v = hsv.v;

    region    = h * 6 / 255;
    remainder = (h * 2 - region * 85) * 3;

    uint8_t third = (remainder * 85) / 255;
    switch (region) {
        case 6:
        case 0: // red -> orange -> yellow
            if (remainder < 128) {
                // red -> orange
                rgb.r = 255;
                rgb.g = third * 2;
                rgb.b = 0;
            } else {
                // orange -> yellow (boost brightness)
                rgb.r = 171;
                rgb.g = 85 + ((remainder - 128) * 170 / 127);
                rgb.b = 0;
            }
            break;
        case 1: // yellow -> green
        {
            uint8_t twothirds = (third * 2);
            rgb.r             = 171 > twothirds ? 171 - twothirds : 0;
            rgb.g             = 170 + third;
            rgb.b             = 0;
        } break;
        case 2: // green -> cyan
            rgb.r = 0;
            rgb.g = 255 - third;
            rgb.b = third;
            break;
        case 3: // cyan -> blue
        {
            uint8_t twothirds = (third * 2);
            rgb.r             = 0;
            rgb.g             = 171 > twothirds ? 171 - twothirds : 0;
            rgb.b             = 85 + twothirds;
        } break;
        case 4: // blue -> magenta
            rgb.r = third;
            rgb.g = 0;
            rgb.b = 255 - third;
            break;
        default: // magenta -> red
            if (remainder < 128) {
                rgb.r = 85 + third;
                rgb.g = 0;
                rgb.b = 171 - third;
            } else {
                rgb.r = 170 + ((remainder - 128) * 85 / 127);
                rgb.g = 0;
                rgb.b = 85 > third ? 85 - third : 0;
            }
            break;
    }

    rgb.g >>= 1;

    if (s != 255) {
        uint8_t desat    = 255 - s;
        desat            = scale8_video(desat, desat);
        uint8_t satscale = 255 - desat;

        rgb.r = scale8(rgb.r, satscale);
        rgb.g = scale8(rgb.g, satscale);
        rgb.b = scale8(rgb.b, satscale);

        uint8_t brightness_floor = desat;
        rgb.r += brightness_floor;
        rgb.g += brightness_floor;
        rgb.b += brightness_floor;
    }

    if (v != 255) {
        v = scale8_video(v, v);
        if (v == 0) {
            rgb.r = 0;
            rgb.g = 0;
            rgb.b = 0;
        } else {
            rgb.r = scale8(rgb.r, v);
            rgb.g = scale8(rgb.g, v);
            rgb.b = scale8(rgb.b, v);
        }
    }

#ifdef USE_CIE1931_CURVE
    if (use_cie) {
        rgb.r = pgm_read_byte(&CIE1931_CURVE[rgb.r]);
        rgb.g = pgm_read_byte(&CIE1931_CURVE[rgb.g]);
        rgb.b = pgm_read_byte(&CIE1931_CURVE[rgb.b]);
    }
#endif

    return rgb;
}

rgb_t hsv_to_rgb(hsv_t hsv) {
#ifdef USE_CIE1931_CURVE
    return hsv_to_rgb_impl(hsv, true);
#else
    return hsv_to_rgb_impl(hsv, false);
#endif
}

rgb_t hsv_to_rgb_nocie(hsv_t hsv) {
    return hsv_to_rgb_impl(hsv, false);
}
