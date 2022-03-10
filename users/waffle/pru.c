// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
#ifdef RANDICT
#include "users/ridingqwerty/dict.h"
uint16_t rand_key;
bool randword_seed = false;
bool random_word(void) {
  bool rbool = rand() & 1;
  return rbool;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
  process_record_user_oled(keycode, record);
#endif
  switch (keycode) {
    case CP_PSTE:
      if (record->event.pressed) {
        tap_code16(C(KC_C));
      } else {
        tap_code16(C(KC_V));
        tap_code(KC_ENT);
      }
      break;
    case ROFL:
      if (record->event.pressed) {
        SEND_STRING("```Incoming ROFLCOPTER!\n"
                    "\n   ROFL:ROFL:ROFL:ROFL\n"
                    "         ___^___ _\n"
                    " L    __/      []  \\ \n"
                    "LOL===__            \\ \n"
                    " L      \\___ ___ ___ ]\n"
                    "           I   I\n"
                    "         ----------/```"SS_TAP(X_ENT));
      }
      break;
    case MT(MOD_LSFT, KC_F23):
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_EXLM);
        } else {
          unregister_code16(KC_EXLM);
        }
      }
      break;
    case MT(MOD_RSFT, KC_F24):
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_RPRN);
        } else {
          unregister_code16(KC_RPRN);
        }
      }
      break;
#ifdef UNICODEMAP_ENABLE
    case HAP:
      if (record->event.pressed) { send_unicode_string("≧ω≦"); } break;
    case TABLE1:
      if (record->event.pressed) { send_unicode_string("┬──┬ ノ( ゜-゜ノ)"); } break;
    case TABLE2:
      if (record->event.pressed) { send_unicode_string("(╯°□°)╯︵┻━┻"); } break;
    case OUT:
      if (record->event.pressed) { send_unicode_string("1F449 1F6AA"); } break;
#endif
#ifdef RANDICT
    case RWORD:
      if (randword_seed == false) {
        randword_seed = true;
        srand(timer_read32());
      }
      rand_key = rand() % NUMBER_OF_WORDS;
      if (record->event.pressed) {
        send_string(dict[rand_key]);
        tap_code(KC_SPC);
      }
      break;
#endif
#ifdef RGB_MATRIX_ENABLE
    case RGB_IDL:
      if (record->event.pressed) {
        userspace_config.rgb_matrix_idle_anim ^= 1;
        dprintf("rgb matrix idle animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
        eeconfig_update_user(userspace_config.raw);
        if (userspace_config.rgb_matrix_idle_anim)
          rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
      }
      break;
#endif
    case MAKE:
      if (!record->event.pressed) {
        SEND_STRING("qmk flash -kb " QMK_KEYBOARD " -km " QMK_KEYMAP
#ifdef BOOTLOADER_DFU
        " -bl dfu"
#elif BOOTLOADER_CATERINA
        " -bl avrdude"
#elif BOOTLOADER_STM32DUINO
        " -bl dfu-util"
#endif
        SS_TAP(X_ENT));
        reset_keyboard();
      }
      break;
    case RST_EEP:
      if (record->event.pressed) {
        eeconfig_init();
        reset_keyboard();
      }
      break;
  }
  return true;
}
