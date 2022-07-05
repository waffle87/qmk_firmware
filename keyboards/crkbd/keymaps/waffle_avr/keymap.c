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

