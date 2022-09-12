#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { LAYOUT_ortho_1x1(KC_A) };

static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
  writePinLow(col_pins[current_col]);
  while (readPin(col_pins[current_col]) != 0)
    ;
  uint16_t porta = palReadPort(GPIOA);
  matrix_row_t rows = ~(porta);
  uint32_t tmp = rows;
  __asm__ volatile("rbit %0, %1" : "=r"(tmp) : "r"(tmp));
  tmp = (tmp >> 24);
  for (int i = 0; i < MATRIX_ROWS; i++) {
    if (tmp & (1 << i))
      current_matrix[i] |= (1ul << current_col);
    else
      current_matrix[i] &= ~(1ul << current_col);
  }
  if (rows == 0)
    return;
  for (size_t i = 0; i < MATRIX_ROWS; i++)
    while (readPin(row_pins[i]) != 1)
      ;
}

bool oled_task_keymap(void) {
  wpm_graph();
  render_wpm();
  return false;
}

/*static void draw_frame(const unsigned char *frame) {
    uint8_t bytes = pgm_read_byte(frame), cursor = 0, i = 1;
    //oled_set_cursor(0, 0); // sets cursor to (row, column) using charactar spacing (5 rows on 128x32 screen, anything more will overflow back to the top)
    while (i < bytes) {
        uint8_t count = pgm_read_byte(frame + i);
        i++;
        if (count & 0x80) {
            count &= ~(0x80);
            for (uint8_t uniqs = 0; uniqs < count; uniqs++) {
                uint8_t value = pgm_read_byte(frame + i);
                i++;
                oled_write_raw_byte(value, cursor);
                cursor++;
            }
        } else {
            uint8_t value = pgm_read_byte(frame + i);
            i++;
            for (uint8_t dup = 0; dup < count; dup++) {
                oled_write_raw_byte(value, cursor);
                cursor++;
            }
        }
    }
}*/

