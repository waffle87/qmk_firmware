#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    _BASE1
    _BASE2
    _BASE3
    _BASE4
  ),
  [_LOWER] = LAYOUT_waffle(
    _LOWER1
    _LOWER2
    _LOWER3
    _LOWER4
  ),
  [_RAISE] = LAYOUT_waffle(
    _RAISE1
    _RAISE2
    _RAISE3
    _RAISE4
  )
};

#ifdef AUDIO_ENABLE
void keyboard_pre_init_user(void) { //thank you to @sigprof for this
  palSetLineMode(A5, PAL_MODE_INPUT_ANALOG);
  palSetLineMode(B1, PAL_MODE_INPUT_ANALOG);
}

void keyboard_post_init_user(void) {
  // enable OPAMP1 as A5 → B1 follower
  OPAMP3->CSR = OPAMP3_CSR_VMSEL_1 | OPAMP3_CSR_VMSEL_0 | OPAMP3_CSR_VPSEL_0 | OPAMP3_CSR_OPAMP3EN;
}
#endif //audio

#ifdef POINTING_DEVICE_ENABLE
extern LED_TYPE rgb_matrix_ws2812_array[DRIVER_LED_TOTAL];
void rgb_matrix_indicators_user(void) {
  pimoroni_trackball_set_rgbw(rgb_matrix_ws2812_array[29].r, rgb_matrix_ws2812_array[29].g, rgb_matrix_ws2812_array[29].b, 0);
}
#endif //rgb matrix

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return 3;
  else
    return 2;
  return rotation;
}

bool oled_task_user(void) {
  if (is_keyboard_master())
    layer_anim();
  else {
    oled_set_cursor(0, 0);
    render_wpm(0);
    oled_set_cursor(0, 3);
    felix();
    oled_set_cursor(0, 7);
    render_keyboard();
    oled_set_cursor(0, 9);
    layer_status();
    oled_set_cursor(0, 11);
    mod_status(get_mods());
    oled_set_cursor(0, 13);
    keylock_status(host_keyboard_led_state());
    oled_set_cursor(1, 15);
    render_keylogger();
    oled_set_cursor(0, 15);
    keylogger_status();
  }
  return false;
}
#endif //oled

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
  [_BASE]  = { { KC_VOLU, KC_VOLD }, { KC_MNXT, KC_MPRV } },
  [_LOWER] = { { RGB_SAI, RGB_SAD }, { RGB_HUI, RGB_HUD } },
  [_RAISE] = { { KC_LEFT, C(KC_RGHT) }, { C(S(KC_TAB)), C(KC_TAB) } }
};
#endif //encoder map
