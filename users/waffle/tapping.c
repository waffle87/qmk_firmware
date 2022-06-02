// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
#include "secrets.h"
#ifdef RANDWORD
#include "users/ridingqwerty/dict.h"
uint16_t word;
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LWRSPC:
    case RSEBSP:
    case ESCLWR:
    case PSTRSE:
      return TAPPING_TERM - 60;
    case LINKS:
    case PNP:
    case TD(EM_DASH):
    case TD(CBRKT):
    case TD(BRKT):
    case TD(BSLS_PIPE):
      return TAPPING_TERM + 40;
    default:
      return TAPPING_TERM;
  }
}

void td_reset(qk_tap_dance_state_t *state, void *user_data) {
  clear_keyboard();
  layer_clear();
}

void qmk_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code16(C(KC_T));
    send_string(qmkstr);
    tap_code(KC_ENT);
  } else {
    tap_code16(C(KC_T));
    send_string(confstr);
    tap_code(KC_ENT);
  }
}

void dash_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1)
    tap_code(KC_MINS);
#ifdef UNICODE_COMMON_ENABLE
  else
    register_unicode(0x2014); //—
#endif
}

void curly_bracket_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1)
    tap_code16(KC_LCBR);
  else
    tap_code16(KC_RCBR);
}

void bracket_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1)
    tap_code(KC_LBRC);
  else
    tap_code(KC_RBRC);
}

void bsls_pipe_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1)
    tap_code(KC_BSLS);
  else
    tap_code16(KC_PIPE);
}

void zero_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1)
    tap_code(KC_0);
#ifdef UNICODE_COMMON_ENABLE
  else
    register_unicode(0x00B0); //°
#endif
}

void media_dance(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code(KC_MPLY);
      break;
    case 2:
      tap_code(KC_MNXT);
      break;
    case 3:
      tap_code(KC_MPRV);
      break;
  }
}

void clipst_search_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed && !state->interrupted)
    layer_on(_RAISE);
  else if (state->count == 1)
    tap_code16(C(S(KC_V)));
  else if (state->count == 2)
    tap_code16(C(S(KC_F)));
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [QMK_LINKS] = ACTION_TAP_DANCE_FN(qmk_dance),
  [EM_DASH] = ACTION_TAP_DANCE_FN(dash_dance),
  [CBRKT] = ACTION_TAP_DANCE_FN(curly_bracket_dance),
  [BRKT] = ACTION_TAP_DANCE_FN(bracket_dance),
  [BSLS_PIPE] = ACTION_TAP_DANCE_FN(bsls_pipe_dance),
  [DEG_0] = ACTION_TAP_DANCE_FN(zero_dance),
  [PLY_NXT_PRV] = ACTION_TAP_DANCE_FN(media_dance),
  [CLIPST_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, clipst_search_dance, td_reset)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!(process_record_keymap(keycode, record)
#ifdef UNICODE_COMMON_ENABLE
  && process_record_unicode(keycode, record)
#endif
  && true))
    return false;
#ifdef OLED_ENABLE
  if (record->event.pressed) {
    oled_timer_reset();
    add_keylog(keycode);
  }
#endif
  switch (keycode) {
    case UPDIR:
      if (record->event.pressed)
        SEND_STRING("../");
      break;
    case EXM_ALT:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_EXLM);
        return false;
      }
      break;
    case AT_GUI:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_AT);
        return false;
      }
      break;
    case HASH_CTL:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_HASH);
        return false;
      }
      break;
    case DLR_SFT:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_DLR);
        return false;
      }
      break;
    case AMPR_SFT:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_AMPR);
        return false;
      }
      break;
    case ASTR_CTL:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_ASTR);
        return false;
      }
      break;
    case LPRN_GUI:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_LPRN);
        return false;
      }
      break;
    case RPRN_ALT:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_RPRN);
        return false;
      }
      break;
    case RWORD:
#ifdef RANDWORD
      word = rand() % NUMBER_OF_WORDS;
      if (record->event.pressed) {
        send_string(dict[word]);
        tap_code(KC_SPC);
      }
#endif
      break;
  }
  return process_record_keymap(keycode, record);
}
