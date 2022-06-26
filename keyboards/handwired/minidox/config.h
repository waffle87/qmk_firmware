#pragma once
#include "config_common.h"
#define VENDOR_ID       0x9237
#define PRODUCT_ID      0x1972
#define DEVICE_VER      0x0000
#define PRODUCT         minidox
#define MATRIX_ROWS 8
#define MATRIX_COLS 5
#define MATRIX_ROW_PINS { F7, B1, B3, B5 }
#define MATRIX_COL_PINS { F6, F5, F4, B6, B4 }
#define MATRIX_ROW_PINS_RIGHT { E6, C6, D4, B3 }
#define MATRIX_COL_PINS_RIGHT { D7, B4, B5, B6, B2 }
#define UNUSED_PINS
#define USE_SERIAL
#define SOFT_SERIAL_PIN D3
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5
