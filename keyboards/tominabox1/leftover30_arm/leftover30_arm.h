/* Copyright 2020 TJ Campie @tominabox1
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
#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18,      k1a, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29,      \
    k30, k31,                k35,           k38, k39       \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a   }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, XXX, k1a   }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, XXX   }, \
    { k30, k31, XXX, XXX, XXX, k35, XXX, XXX, k38, k39, XXX   }  \
}

#define LAYOUT_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18,      k1a, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28,           \
    k30, k31,                k35,           k38, k39       \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a   }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, XXX, k1a   }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, XXX, XXX   }, \
    { k30, k31, XXX, XXX, XXX, k35, XXX, XXX, k38, k39, XXX   }  \
}
