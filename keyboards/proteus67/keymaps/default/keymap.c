// Copyright 2023 James Gzowski
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layer {
    _LAYERA,
    _LAYERB,
    _LAYERC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYERA] = LAYOUT_ortho_5x14(
        KC_ESC , KC_1  ,KC_2   ,KC_3   , KC_4  , KC_5  , KC_MINUS  , 			KC_EQL  , KC_6   , KC_7    , KC_8    , KC_9   , KC_0   , KC_GRV ,
        KC_TAB , KC_Q  ,KC_W   ,KC_E   , KC_R  , KC_T  , KC_END  , 			KC_HOME  , KC_Y   , KC_U    , KC_I    , KC_O   , KC_P   ,KC_MINUS,
        KC_LCTL, KC_A  ,KC_S   ,KC_D   , KC_F  , KC_G  , KC_PGDN  , 			KC_PGUP  , KC_H   , KC_J    , KC_K    , KC_L   , KC_SCLN,KC_QUOT ,
        KC_LSFT, KC_Z  ,KC_X   ,KC_C   , KC_V  , KC_B  , KC_LBRC, 			KC_RBRC, KC_N   , KC_M    , KC_COMM , KC_DOT , KC_SLSH, KC_RSFT,
             KC_NO  , MO(_LAYERB) ,KC_LGUI,KC_LALT,       KC_SPC ,		KC_MUTE,            KC_ENT ,		KC_BSPC , MO(_LAYERC) , KC_INS , KC_DEL
),
    [_LAYERB] = LAYOUT_ortho_5x14(
        UG_TOGG , UG_HUEU  ,UG_HUED   ,UG_SATU   , UG_SATD  , UG_VALU  , UG_VALD  ,                       RGB_M_P  , RGB_M_B   , RGB_M_R    , RGB_M_SW    , RGB_M_K   , RGB_M_X   , RGB_M_G ,
        KC_TRNS , KC_TRNS, KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS  ,              KC_TRNS  , KC_TRNS , MS_BTN1    , MS_UP      , MS_BTN2   , KC_TRNS   ,KC_TRNS,
        KC_TRNS, KC_TRNS  ,KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS  ,              KC_TRNS  , KC_TRNS , MS_LEFT    , MS_DOWN , MS_RGHT , KC_SCLN,KC_QUOT ,
        KC_TRNS, KC_TRNS  ,KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS ,               KC_TRNS  , KC_TRNS , KC_TRNS    , KC_TRNS , KC_TRNS , KC_NUBS, KC_TRNS,
             KC_TRNS  , KC_TRNS ,KC_TRNS,KC_TRNS,  KC_TRNS ,                       UG_PREV,       KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
),
    [_LAYERC] = LAYOUT_ortho_5x14(
        KC_TRNS , KC_F1  ,KC_F2   ,KC_F3   , KC_F4  , KC_F5  , KC_TRNS  ,                       KC_TRNS  , KC_F6   , KC_F7    , KC_F8    , KC_F9   , KC_F10   , KC_GRV ,
        KC_TRNS , KC_TRNS, KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS  ,              KC_TRNS  , KC_TRNS , KC_TRNS    , KC_UP    , KC_TRNS   , KC_TRNS   ,KC_TRNS,
        KC_TRNS, KC_TRNS  ,KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS  ,              KC_TRNS  , KC_TRNS , KC_LEFT    , KC_DOWN , KC_RIGHT , KC_SCLN,KC_QUOT ,
        KC_TRNS, KC_TRNS  ,KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS ,               KC_TRNS  , KC_TRNS , KC_TRNS    , KC_TRNS , KC_TRNS , KC_NUBS, KC_TRNS,
             KC_TRNS  , KC_TRNS ,KC_TRNS,KC_TRNS,  KC_TRNS ,                       UG_NEXT,      KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAYERA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LAYERB] =  { ENCODER_CCW_CW(UG_HUED, UG_HUEU)},
    [_LAYERC] =  { ENCODER_CCW_CW(UG_VALD, UG_VALU)}
};
#endif
