// Copyright 2023 Kyle McCreery
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
	_LOWER,
	_RAISE,
    _ADJUST,
    _MOUSE,
    _STENO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(                                                            
    QK_GESC, KC_Q, KC_W,    KC_E,    KC_R,       KC_T,                          TAP_UP,       KC_Y,   KC_U,     KC_I,   KC_O,    KC_P, KC_BSPC, 
    KC_LCTL, KC_A, KC_S,    KC_D,    KC_F,       KC_G,             KC_MUTE,     TAP_DN,       KC_H,   KC_J,     KC_K,   KC_L, KC_QUOT,  KC_ENT, 
    KC_LSFT, KC_Z, KC_X,    KC_C,    KC_V,       KC_B,                      TG(_STENO),       KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,    
          KC_MUTE,       KC_LGUI, KC_LALT, TL_LOWR, MS_BTN1, TAP_TOG, MS_BTN2, TL_UPPR, KC_SPC,  KC_RSFT,         KC_MUTE
  ),
  [_LOWER] = LAYOUT(                                                 
    KC_TRNS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                    DPI_UP,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,         
    KC_TRNS, KC_MINS,  KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  DPI_DN, KC_TRNS, KC_LBRC, KC_RBRC, KC_BSLS, KC_SCLN, KC_SCLN,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_TRNS,
             KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS            
  ),                                                                                                                 
  [_RAISE] = LAYOUT(                                                                                                 
    KC_TRNS, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
    KC_TRNS, KC_UNDS, KC_PLUS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_PIPE, KC_DQUO, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_TRNS,
             KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS            
  ),                                                                                                                 
  [_ADJUST] = LAYOUT(                                                                                                
    KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                   KC_TRNS,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_TRNS,
    KC_TRNS,  KC_F11,  KC_F12, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, UG_VALD, UG_PREV,  UG_TOGG,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, UG_VALU, UG_NEXT,  KC_TRNS,
             KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS
  ),
  [_MOUSE] = LAYOUT(                                                                                                
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS,          DPI_FINE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS
  ),
    [_STENO] = LAYOUT(                                                                                                
      STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,                   KC_TRNS,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC, 
    STN_RES1,  STN_S1,  STN_TL,  STN_PL,  STN_HL, STN_ST1,          KC_TRNS, KC_TRNS, STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,         
    STN_RES2,  STN_S2,  STN_KL,  STN_WL,  STN_RL, STN_ST2,                   KC_TRNS, STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR, 
              KC_TRNS,           STN_N1,   STN_A,   STN_O, KC_TRNS, KC_TRNS, KC_TRNS,   STN_E,   STN_U,  STN_N2,          KC_TRNS
  )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN),  ENCODER_CCW_CW(MS_WHLU, MS_WHLD)  },
    [_LOWER] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_HOME, KC_END),   ENCODER_CCW_CW(DPI_UP, DPI_DN)    },
    [_RAISE] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_HOME, KC_END),   ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_HOME, KC_END)   },
    [_ADJUST] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_BRID, KC_BRIU),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_BRID, KC_BRIU)  },
    [_MOUSE] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_BRID, KC_BRIU),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_BRID, KC_BRIU)  },
    [_STENO] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_HOME, KC_END),   ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_HOME, KC_END)   }
};
#endif

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
}
