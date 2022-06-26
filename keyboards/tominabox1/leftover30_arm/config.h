#pragma once
#include "config_common.h"
#define VENDOR_ID 0x7431
#define PRODUCT_ID 0x4C4F
#define DEVICE_VER 0x0001
#define PRODUCT leftover30

#define MATRIX_ROWS 4
#define MATRIX_COLS 11
#define MATRIX_ROW_PINS { B3, B4, C13, A5 }
#define MATRIX_COL_PINS { A15, B9, B8, B7, B6, B5, C14, C15, F1, F0, A1 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { B12, A7 }
#define ENCODERS_PAD_B { B14, B0 }

#define RGB_DI_PIN B15
#define RGBLED_NUM 8
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LED_MAP { 0, 1,  3, 4, 5, 6, 2, 7 }

#define WS2812_SPI SPID2
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_EXTERNAL_PULLUP
