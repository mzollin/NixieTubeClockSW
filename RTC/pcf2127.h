// Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>
// GNU General Public License Version 3

#ifndef PCF2127_H_
#define PCF2127_H_

#include "../datetimebcd_type.h"
#include <avr/io.h>

#define SDA PC4
#define SCL PC5

enum { PCF2127_ADDR = 0xA2 };

enum { CLKOUT_CTL_REG = 0x0F };
enum { OTPR_OFFSET = 5 };
enum { OTPR_REFRESH_VAL = 0x00,
       OTPR_DEFAULT_VAL = 0x01 };
enum { OTPR_TIMEOUT = 100 };
enum { TCR_OFFSET = 6 };
enum { TCR_30SEC_VAL = 0x03 };
enum { COF_OFFSET = 0 };
enum { COF_1024HZ_VAL = 0x05 };

enum { DATETIME_START_REG = 0x03 };
enum { DATETIME_SIZE = 7 };
enum { OSF_BYTE = 0 };
enum { OSF_OFFSET = 7 };
enum { OSF_OK_VAL = 0x00 };
enum { SECONDS_BYTE = 0 };
enum { MINUTES_BYTE = 1 };
enum { HOURS_BYTE = 2 };
enum { DAYS_BYTE = 3 };
enum { WEEKDAYS_BYTE = 4 };
enum { MONTHS_BYTE = 5 };
enum { YEARS_BYTE = 6 };

uint8_t pcf2127_init(void);
uint8_t pcf2127_refresh_otp(void);
//uint8_t pcf2127_get_datetime(uint8_t (* const datetime)[DATETIME_SIZE]);
//uint8_t pcf2127_set_datetime(const uint8_t (* const datetime)[DATETIME_SIZE]);
uint8_t pcf2127_get_datetime(DatetimeBcd *const datetime);
uint8_t pcf2127_set_datetime(const DatetimeBcd *const datetime);

#endif /* PCF2127_H_ */