// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
#ifdef RANDICT
#include "users/ridingqwerty/dict.h"
uint16_t word;
bool randword_seed = false;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!(process_record_keymap(keycode, record)
#ifdef UNICODE_COMMON_ENABLE
  && process_record_unicode(keycode, record)
#endif
  && true))
    return false;
#ifdef OLED_ENABLE
  if (record->event.pressed)
    add_keylog(keycode);
#endif
  switch (keycode) {
    case CP_PSTE:
      if (record->event.pressed)
        tap_code16(C(KC_C));
      else
        tap_code16(C(KC_V));
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
                    "         ----------/```");
      }
      break;
    case SFEXM:
      if (record->tap.count > 0) {
        if (record->event.pressed)
          register_code16(KC_EXLM);
        else
          unregister_code16(KC_EXLM);
      }
      break;
    case SFPRN:
      if (record->tap.count > 0) {
        if (record->event.pressed)
          register_code16(KC_RPRN);
        else
          unregister_code16(KC_RPRN);
      }
      break;
    case RWORD:
#ifdef RANDICT
      if (randword_seed == false) {
        randword_seed = true;
        srand(timer_read32());
      }
      word = rand() % NUMBER_OF_WORDS;
      if (record->event.pressed) {
        send_string(dict[word]);
        tap_code(KC_SPC);
      }
#endif
      break;
    case RST_EEP:
      if (record->event.pressed) {
        eeconfig_init();
        reset_keyboard();
      }
      break;
  }
  return process_record_keymap(keycode, record);
}
