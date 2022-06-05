// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
uint8_t current_tap_frame = 0;
uint16_t log_timer = 0;
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
led_t led_usb_state;
bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;
bool anim_phase = false;
char keylog_str[5] = {};
__attribute__((weak)) void suspend_power_down_user(void) { oled_off(); }

#ifdef WPM_ENABLE
void render_wpm(void) { //thanks to sigprof/drashna for this
  uint8_t n = get_current_wpm();
  char wpm_counter[6];
  wpm_counter[5] = '\0';
  wpm_counter[4] = '0' + n % 10;
  wpm_counter[3] = ( n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
  wpm_counter[2] = n / 10 ? '0' + n / 10 : ' ';
  wpm_counter[1] = ' ';
  wpm_counter[0] = ' ';
  oled_write_P(PSTR("WPM:"), false);
  oled_write(wpm_counter, false);
}
#endif

#ifdef DEBUG_MATRIX_SCAN_RATE
void maxtrix_scan_rate(void) { //matrix scan rate
  char matrix_rate[5];
  uint16_t n = get_matrix_scan_rate();
  matrix_rate[4] = '\0';
  matrix_rate[3] = '0' + n % 10;
  matrix_rate[2] = (n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
  matrix_rate[1] = n / 10 ? '0' + n / 10 : ' ';
  matrix_rate[0] = ' ';
  oled_write(matrix_rate, false);
  oled_write_P(PSTR("/s"), false);
}
#endif

#ifdef POINTING_DEVICE_ENABLE
kb_config_data_t kb_config;
void pointing_device_dpi(uint8_t padding) {
  oled_write_P(PSTR("CPI:"), false);
  if (padding) {
    for (uint8_t i = padding - 1; i > 0; i--) {
      oled_write_P(PSTR(" "), false);
    }
  }
  oled_write(get_u16_str(kb_config.device_cpi, ' '), false);
}
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_info(void) {
  HSV color = rgb_matrix_get_hsv();
  oled_write_raw_byte(color.h, false);
  oled_write_raw_byte(color.s, false);
  oled_write_raw_byte(color.v, false);
}
#endif

void render_qmk_logo(void) { //qmk logo
  static const char PROGMEM font_qmk_logo[16] = {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0};
  oled_write_P(font_qmk_logo, false);
};

void render_keyboard(void) { //split keyboard
  static const char PROGMEM font_keyboard[16] = {0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0};
  oled_write_P(font_keyboard, false);
};

void render_mod_ctrl(void) { // ^
  static const char PROGMEM font_ctrl[3] = {0x93, 0x94, 0};
  oled_write_P(font_ctrl, false);
};

void render_mod_alt(void) { // ⌥
  static const char PROGMEM font_alt[3] = {0xb3, 0xb4, 0};
  oled_write_P(font_alt, false);
};

void render_mod_shift(void) { // ⇧
  static const char PROGMEM font_shift[3] = {0xd3, 0xd4, 0};
  oled_write_P(font_shift, false);
};

void render_mod_gui(void) { // win symbol
  static const char PROGMEM font_gui[3] = {0x95, 0x96, 0};
  oled_write_P(font_gui, false);
};

void render_prompt(void) { //layer state indicator
  bool blink = (timer_read() % 1000) < 500;
  if (layer_state_is(1))
    oled_write_ln_P(blink ? PSTR("> lo_") : PSTR("> lo "), false);
  else if (layer_state_is(2))
    oled_write_ln_P(blink ? PSTR("> hi_") : PSTR("> hi "), false);
  else if (layer_state_is(3))
    oled_write_ln_P(blink ? PSTR("> ad_") : PSTR("> ad "), false);
  else
    oled_write_ln_P(blink ? PSTR("> _ ") : PSTR(">     "), false);
};

void render_mod_status(void) { //active modifier indicator
  bool blink = (timer_read() % 1000) < 500;
  uint8_t modifiers = get_mods();
  if (modifiers & MOD_MASK_CTRL)
    oled_write_ln_P(blink ? PSTR("$ ctl") : PSTR("$ _  "), false);
  else if (modifiers & MOD_MASK_SHIFT)
    oled_write_ln_P(blink ? PSTR("$ sft") : PSTR("$ _  "), false);
  else if (modifiers & MOD_MASK_ALT)
    oled_write_ln_P(blink ? PSTR("$ alt") : PSTR("$ _  "), false);
  else if (modifiers & MOD_MASK_GUI)
    oled_write_ln_P(blink ? PSTR("$ gui") : PSTR("$ _  "), false);
  else
    oled_write_ln_P(blink ? PSTR("$ _  ") : PSTR("$    "), false);
}

void render_keylock_status(uint8_t led_usb_state) { //active keylock indicator (caps, num, scroll)
  bool blink = (timer_read() % 1000) < 500;
  if (led_usb_state & (1 << USB_LED_CAPS_LOCK))
    oled_write_ln_P(blink ? PSTR("% cap") : PSTR("% _  "), false);
  else if (led_usb_state & (1 << USB_LED_NUM_LOCK))
    oled_write_ln_P(blink ? PSTR("% num") : PSTR("% _  "), false);
  else if (led_usb_state & (1 << USB_LED_SCROLL_LOCK))
    oled_write_ln_P(blink ? PSTR("% scr") : PSTR("% _  "), false);
  else
    oled_write_ln_P(blink ? PSTR("% _  ") : PSTR("%    "), false);
}

const char code_to_name[60] = {
  ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
  '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
};

void add_keylog(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX))
    keycode = keycode & 0xFF;
  for (uint8_t i = 4; i > 0; i--)
    keylog_str[i] = keylog_str[i - 1];
  if (keycode < 60)
    keylog_str[0] = code_to_name[keycode];
  keylog_str[4] = 0;
  log_timer = timer_read();
}

void update_log(void) {
  if (timer_elapsed(log_timer) > 750)
    add_keylog(0);
}

void render_keylogger(void) { oled_write(keylog_str, false); } //keylogger data

void render_keylogger_status(void) { //keylogger prompt
  bool blink = (timer_read() % 1000) < 500;
  oled_write_ln_P(blink ? PSTR("~ _") : PSTR("~  "), false);
}

#ifdef FELIX
void felix_frame(char const action[][96]) {
  static uint8_t current_frame = 0;
  current_frame = (current_frame + 1) & 1;
  oled_write_raw_P(action[current_frame], 96);
}

void render_felix(void) {
  static uint8_t prev_wpm = 0;
  static uint16_t anim_timer = 0;
  uint32_t tap_timer = 0;
  if (get_current_wpm() > prev_wpm || get_mods())
    tap_timer = timer_read32();
  prev_wpm = get_current_wpm();
  void animate_felix(void) {
    if (get_mods() & MOD_MASK_SHIFT || host_keyboard_led_state().caps_lock)
      felix_frame(bark);
    else if (get_mods() & MOD_MASK_CAG)
      felix_frame(sneak);
    else if (timer_elapsed32(tap_timer) < 400)
      felix_frame(run);
    else if (timer_elapsed32(tap_timer) < 1600)
      felix_frame(walk);
    else
      felix_frame(sit);
  }
  if (timer_elapsed32(tap_timer) > OLED_TIMEOUT)
    oled_off();
  else if (timer_elapsed(anim_timer) > 200) {
    anim_timer = timer_read();
    animate_felix();
  }
}
#endif

#ifdef BONGO_CAT
void render_bongo(void) { //solid-filled bongo cat animation
  uint8_t current_idle_frame = 0;
  void animation_phase(void) {
    if (get_current_wpm() <= 30) {
      current_idle_frame = (current_idle_frame + 1) % 5;
      oled_write_raw_P(bongo_idle[abs((4) - current_idle_frame)], 512);
    } if (get_current_wpm() > 30 && get_current_wpm() < 40) {
      oled_write_raw_P(bongo_prep[0], 512);
    } if (get_current_wpm() >= 40) {
      current_tap_frame = (current_tap_frame + 1) % 2;
      oled_write_raw_P(bongo_tap[abs((1) - current_tap_frame)], 512);
    }
  }

  if (get_current_wpm() != 000) {
    if (timer_elapsed32(anim_timer) > 200) {
      anim_timer = timer_read32();
      animation_phase();
    }
    anim_sleep = timer_read32();
  }  else if (timer_elapsed32(anim_timer) > 200) {
    anim_timer = timer_read32();
    animation_phase();
  }
}
#endif

#ifdef KIRBY
void render_kirby(void) {
  bool showed_jump = true;
  uint8_t current_idle_frame = 0;
  uint8_t current_walk_frame = 0;
  uint8_t current_jump_frame = 0;
  uint8_t current_inhale_frame = 0;
  uint8_t current_exhale_frame = 0;
  uint8_t caps_state = 0;
  uint8_t get_frame_duration(void) { return max(200 - (get_current_wpm() * 0.65), 75); }
  void animate_kirby(void) {
    if (get_current_wpm() <= 20) {
      current_idle_frame = (current_idle_frame + 1) % 2;
      if (led_usb_state.caps_lock)
        oled_write_raw_P(kirby_caps_idle[abs((1) - current_idle_frame)], 512);
      else
        oled_write_raw_P(kirby_idle[abs((1) - current_idle_frame)], 512);
    } else {
      if (led_usb_state.caps_lock) {
        current_walk_frame = (current_walk_frame + 1) % 2;
        oled_write_raw_P(kirby_caps_walk[abs((1) - current_walk_frame)], 512);
      } else {
        current_walk_frame = (current_walk_frame + 1) % 4;
        oled_write_raw_P(kirby_walk[abs((3) - current_walk_frame)], 512);
      }
    }
  }
  if (caps_state == 1) {
    if (timer_elapsed32(anim_timer) > 95) {
      oled_write_raw_P(kirby_inhale[min(current_inhale_frame, (2))], 512);
      current_inhale_frame += 1;
      anim_timer = timer_read32();
      if (current_inhale_frame > 2)
        caps_state = 2;
    }
  } else if (caps_state == 3) {
    if (timer_elapsed32(anim_timer) > 95) {
      oled_write_raw_P(kirby_exhale[min(current_exhale_frame, (2))], 512);
      current_exhale_frame += 1;
      anim_timer = timer_read32();
      if (current_exhale_frame > 2)
        caps_state = 0;
    }
  } else if (!showed_jump) {
    if (timer_elapsed32(anim_timer) > 50) {
      oled_write_raw_P(kirby_jump[min(current_jump_frame, (2))], 512);
      current_jump_frame += 1;
      anim_timer = timer_read32();
      if (current_jump_frame > 2)
        showed_jump = true;
    }
  } else {
    if (led_usb_state.caps_lock && caps_state == 0) {
      current_inhale_frame = 0;
      caps_state = 1;
    } else if (!led_usb_state.caps_lock && caps_state == 2) {
      current_exhale_frame = 0;
      caps_state = 3;
    } else if (showed_jump && !led_usb_state.caps_lock) {
      current_jump_frame = 0;
      showed_jump = false;
    } else if (get_mods() & MOD_MASK_CTRL && !led_usb_state.caps_lock)
      oled_write_raw_P(kirby_jump[2], 512);
    else {
      if ((get_current_wpm() <= 20 && timer_elapsed32(anim_timer) > 600) || (get_current_wpm() > 20 && timer_elapsed32(anim_timer) > (led_usb_state.caps_lock ? get_frame_duration() * 2 : get_frame_duration())) || (current_jump_frame > 0 && timer_elapsed32(anim_timer) > 50) || (current_inhale_frame > 0 && timer_elapsed32(anim_timer) > 95) || (current_exhale_frame > 0 && timer_elapsed32(anim_timer) > 95)) {
        animate_kirby();
        anim_timer = timer_read32();
        current_jump_frame = 0;
        current_inhale_frame = 0;
        current_exhale_frame = 0;
      }
    }
  }
}
#endif

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed)
    add_keylog(keycode);
  return true;
#ifdef FELIX
  switch (keycode) {
    case KC_SPC:
      if (record->event.pressed) {
        isJumping = true;
        showedJump = false;
      } else {
        isJumping = false;
      }
      break;
    case KC_LCTL:
    case KC_RCTL:
      if (record->event.pressed)
        isSneaking = true;
      else
       isSneaking = false;
      break;
  }
#endif
  return true;
}

#ifdef LAYER_ANIM
void animation_run(void) {
  if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT)
    oled_off();
  else {
    anim_timer = timer_read32();
    anim_phase = true;
  }
}

static void render_anim_num(void) { //number pad animation
  if (anim_phase == true) {
    current_tap_frame = (current_tap_frame + 1) % 3;
    oled_write_raw_P(tap_num[abs((2) - current_tap_frame)], 520);
    anim_phase = false;
  }
  animation_run();
}

static void render_anim_sym(void) { //angry symbols animation
  if (anim_phase == true) {
    current_tap_frame = (current_tap_frame + 1) % (4);
    oled_write_raw_P(tap_sym[abs((2) - current_tap_frame)], 650);
    anim_phase = false;
  }
  animation_run();
}

static void render_anim_sys(void) { //system console like animation
  if (anim_phase == true) {
    current_tap_frame = (current_tap_frame + 1) % (4);
    oled_write_raw_P(tap_sys[abs((2) - current_tap_frame)], 520);
    anim_phase = false;
  }
  animation_run();
}
#endif

void render_main(void) {
  oled_set_cursor(0, 0);
  render_wpm();
  oled_set_cursor(0, 3);
  render_qmk_logo();
  oled_set_cursor(0, 7);
  render_keyboard();
  oled_set_cursor(0, 9);
  render_prompt();
  oled_set_cursor(0, 11);
  render_mod_status();
  oled_set_cursor(0, 13);
  render_keylock_status(host_keyboard_leds());
  oled_set_cursor(1, 15);
  render_keylogger();
  oled_set_cursor(0, 15);
  render_keylogger_status();
}

void render_secondary(void) {
  switch (get_highest_layer(layer_state)) {
    case _LOWER:
      render_anim_num();
      break;
    case _RAISE:
      render_anim_sym();
      break;
    case _ADJUST:
      render_anim_sys();
      break;
    default:
      render_bongo();
      break;
  }
}
