// Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>
// GNU General Public License Version 3

#define F_CPU 11059200UL

#include "pcf2127.h"
#include "i2cmaster.h"
#include <util/delay.h>

uint8_t pcf2127_init(void) {
    i2c_init();
    pcf2127_refresh_otp();
    uint8_t error = i2c_start(PCF2127_ADDR + I2C_WRITE);
    error |= i2c_write(CLKOUT_CTL_REG);
    error |= i2c_write((OTPR_DEFAULT_VAL << OTPR_OFFSET) |
                       (TCR_30SEC_VAL << TCR_OFFSET) |
                       (COF_1024HZ_VAL << COF_OFFSET));
    i2c_stop();
    return error;
}

uint8_t pcf2127_refresh_otp(void) {
    uint8_t error = i2c_start(PCF2127_ADDR + I2C_WRITE);
    error |= i2c_write(CLKOUT_CTL_REG);
    error |= i2c_write(OTPR_REFRESH_VAL);
    i2c_stop();
    _delay_ms(OTPR_TIMEOUT);
    return error;
}

uint8_t pcf2127_get_datetime(DatetimeBcd *const datetime) {
    uint8_t error = i2c_start(PCF2127_ADDR + I2C_WRITE);
    error |= i2c_write(DATETIME_START_REG);
    // repeated start not allowed for PCF2127
    i2c_stop();
    _delay_ms(1);
    error |= i2c_start(PCF2127_ADDR + I2C_READ);
    for (uint8_t i = 0; i < DATETIME_SIZE; ++i) {
        if (i < DATETIME_SIZE - 1) {
            datetime->all[i] = i2c_readAck();
        } else {
            datetime->all[i] = i2c_readNak();
        }
    }
    i2c_stop();
    return error;
}

uint8_t pcf2127_set_datetime(const DatetimeBcd *const datetime) {
    uint8_t error = i2c_start(PCF2127_ADDR + I2C_WRITE);
    error |= i2c_write(DATETIME_START_REG);
    for (uint8_t i = 0; i < DATETIME_SIZE; ++i) {
        error |= i2c_write(datetime->all[i]);
    }
    i2c_stop();
    return error;
}