// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define IGNORE_MOD_TAP_INTERRUPT
#define PERSMISSVE_HOLD
#define TAPPING_TERM 150
#define LAYER_STATE_8BIT
#define FORCE_NKRO
#define TAPPING_TERM_PER_KEY
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define COMBO_TERM 50
#define NO_ACTION_ONESHOT
#define UNICODE_SELECTED_MODES UC_LNX
#define ENABLE_COMPILE_KEYCODE
#undef MANUFACTURER
#define MANUFACTURER waffles

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_EFFECTS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif

#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 600000
#    define OLED_FONT_H "users/waffle/oledfont.h"
#    define OLED_UPDATE_INTERVAL 100
#endif

#ifdef SPLIT_KEYBOARD
#    define MASTER_RIGHT
#    define SPLIT_MODS_ENABLE
#    define SPLIT_WPM_ENABLE
#    define SPLIT_LAYER_STATE_ENABLE
#    define SPLIT_OLED_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#endif
