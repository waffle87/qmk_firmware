#include "mcp23018.h"
#include "quantum.h"

#pragma GCC push_options
#pragma GCC optimize("-O3")
#pragma GCC pop_options

#define I2C_ADDR 0b0100000 //0x20 ?

static uint16_t mcp23018_reset_loop = 0;
static uint8_t mcp23018_errors = 0;

static const pin_t row_pins[MATRIX_ROWS / 2] = {F5, F1, D3, B5};
static const pin_t col_pins[MATRIX_COLS] = {F7, D2, D4, D6, D7, B4};

static void select_row(uint8_t row) {
  setPinOutput(row_pins[row]);
  writePinLow(row_pins[row]);
}

static void unselect_row(uint8_t row) {
  setPinInputHigh(row_pins[row]);
}

static void unselect_rows(void) {
  for (uint8_t i = 0;i < MATRIX_ROWS / 2; i++)
    setPinInputHigh(row_pins[i]);
}

static void init_pins(void) {
  unselect_rows();
  for (uint8_t i = 0; i < MATRIX_COLS; i++)
    setPinInputHigh(col_pins[i]);
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
  matrix_row_t last_row_value = current_matrix[current_row];
  matrix_row_t current_row_value = 0;
  select_row(current_row);
  wait_us(5);
  for (uint8_t i = 0; i < MATRIX_COLS; i++) {
    uint8_t pin_state = readPin(col_pins[i]);
    current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << i);
  }
  unselect_row(current_row);
  if (last_row_value == current_row_value)
    return false;
  current_matrix[current_row] = current_row_value;
  return true;
}

static void init_pins_MCP23018(void) {
  mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTA, 0b11111111);
  mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTB, 0b01100000);
}

static void select_row_MCP23018(uint8_t row) {
  uint8_t mask = 0;
  switch (row) {
    case 6:
      mask = 0b10000000;
      break;
    case 7:
      mask = 0b00000001;
      break;
    case 8:
      mask = 0b00000010;
      break;
    case 9:
      mask = 0b00000100;
      break;
    case 10:
      mask = 0b00001000;
      break;
    case 11:
      mask = 0b00010000;
      break;
  }
  mcp23018_errors += !mcp23018_set_output(I2C_ADDR, mcp23018_PORTB, ~mask);
}

static uint16_t read_cols_MCP23018(void) {
  uint16_t temp = 0xFFFF;
  mcp23018_errors += !mcp23018_readPins_all(I2C_ADDR, &temp);
  uint16_t state = ((temp & 0b11111111) << 2) | ((temp & 0b0110000000000000) >> 13);
  return (~state) & 0b1111111111;
}

static bool read_cols_on_row_MCP23018(matrix_row_t current_matrix[], uint8_t current_row) {
  matrix_row_t last_row_value = current_matrix[current_row];
  select_row_MCP23018(current_row);
  matrix_row_t current_row_value = read_cols_MCP23018();
  if (last_row_value == current_row_value)
    return false;
  current_matrix[current_row] = current_row_value;
  return true;
}

void matrix_init_custom(void) {
  mcp23018_init(I2C_ADDR);
  init_pins();
  init_pins_MCP23018();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  bool changed = false;
  for (uint8_t i = 0; i < MATRIX_ROWS / 2; i++)
    changed |= read_cols_on_row(current_matrix, i);
  if (mcp23018_errors) {
    if (++mcp23018_reset_loop > 0x7FFF) {
      print("attempting reset mcp23018\n");
      mcp23018_reset_loop = 0;
      mcp23018_errors = 0;
      init_pins_MCP23018();
    }
    return changed;
  }
  for (uint8_t i = MATRIX_ROWS / 2; i < MATRIX_ROWS; i++)
    changed |= read_cols_on_row_MCP23018(current_matrix, i);
  return changed;
}
