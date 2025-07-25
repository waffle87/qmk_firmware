// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
#include "cirque_pinnacle.h"
#include "i2c_master.h"
#include "stdio.h"

// Masks for Cirque Register Access Protocol (RAP)
#define WRITE_MASK 0x80
#define READ_MASK 0xA0

/*  RAP Functions */
// Reads <count> Pinnacle registers starting at <address>
void RAP_ReadBytes(uint8_t address, uint8_t* data, uint8_t count) {
    uint8_t cmdByte = READ_MASK | address; // Form the READ command byte
    i2c_write_register(CIRQUE_PINNACLE_ADDR << 1, cmdByte, NULL, 0, CIRQUE_PINNACLE_TIMEOUT);
    if (i2c_read_register(CIRQUE_PINNACLE_ADDR << 1, cmdByte, data, count, CIRQUE_PINNACLE_TIMEOUT) != I2C_STATUS_SUCCESS) {
        pd_dprintf("error cirque_pinnacle i2c_read_register\n");
        pointing_device_set_status(POINTING_DEVICE_STATUS_FAILED);
    }
}

// Writes single-byte <data> to <address>
void RAP_Write(uint8_t address, uint8_t data) {
    uint8_t cmdByte = WRITE_MASK | address; // Form the WRITE command byte
    if (i2c_write_register(CIRQUE_PINNACLE_ADDR << 1, cmdByte, &data, sizeof(data), CIRQUE_PINNACLE_TIMEOUT) != I2C_STATUS_SUCCESS) {
        pd_dprintf("error cirque_pinnacle i2c_write_register\n");
        pointing_device_set_status(POINTING_DEVICE_STATUS_FAILED);
    }
}
