MCU = atmega32u4
BOOTLOADER = atmel-dfu
CUSTOM_MATRIX = lite
VPATH += drivers/gpio
SRC += mcp23018.c matrix.c
QUANTUM_LIB_SRC += i2c_master.c
