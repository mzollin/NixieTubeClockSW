/*
 * Copyright (C) 2021 Marco Zollinger <marco@freelabs.space>
 * GNU General Public License Version 3
 */

#ifndef PCF2127_H_
#define PCF2127_H_

#include "../datetimebcd_type.h"
#include <avr/io.h>

#define SDA PC4
#define SCL PC5

enum { PCF2127_ADDR = 0xA2 };

/*
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
*/

/* Control and status register 1 (address 0x00h) */
typedef union {
    struct {
        bool si         : 1;    // second interrupt enable
        bool mi         : 1;    // minute interrupt enable
        bool hm         : 1;    // 12 hour mode enable
        bool por_ovrd   : 1;    // power-on reset override
        bool tsf1       : 1;    // timestamp interrupt flag 1
        bool stop       : 1;    // RTC clock stop
        bool            : 1;    // unused
        bool ext_test   : 1;    // external clock test mode
    } __attribute__((__packed__));
    uint8_t raw;
} ctl_1_reg_t;

/* Control and status register 2 (address 0x01h) */
typedef union {
    struct {
        bool cdtie  : 1;    // countdown timer interrupt enable
        bool aie    : 1;    // alarm interrupt enable
        bool tsie   : 1;    // timestamp interrupt enable
        bool cdtf   : 1;    // countdown timer interrupt flag
        bool af     : 1;    // alarm interrupt flag
        bool tsf2   : 1;    // timestamp interrupt flag 2
        bool wdtf   : 1;    // watchdog timer interrupt flag
        bool msf    : 1;    // minute or second interrupt flag
    } __attribute__((__packed__));
    uint8_t raw;
} ctl_2_reg_t;

/* Control and status register 3 (address 0x02h) */
typedef union {
    struct {
        bool blie       : 1;    // battery low interrupt enable
        bool bie        : 1;    // battery switch-over interrupt enable
        bool blf        : 1;    // battery low interrupt flag
        bool bf         : 1;    // battery switch-over interrupt flag
        bool btse       : 1;    // battery switch-over timestamp enable
        uint8_t pwrmng  : 3;    // power management control bits
    } __attribute__((__packed__));
    uint8_t raw;
} ctl_3_reg_t;

/* Second timekeeping and clock integrity register (address 0x03h) */
typedef union {
    struct {
        uint8_t second_units    : 4;    // second (units digit) in BCD
        uint8_t second_tens     : 3;    // second (tens digit) in BCD
        bool osf                : 1;    // clock integrity bad flag
    } __attribute__((__packed__));
    uint8_t raw;
} sec_reg_t;

/* Minute timekeeping register (address 0x04h) */
typedef union {
    struct {
        uint8_t minute_units    : 4;    // minute (units digit) in BCD
        uint8_t minute_tens     : 3;    // minute (tens digit) in BCD
        uint8_t                 : 1;    // unused
    } __attribute__((__packed__));
    uint8_t raw;
} min_reg_t;

/* Hour timekeeping register (address 0x05h) */
typedef union {
    struct {
        uint8_t hour_units      : 4;    // hour (units digit) in BCD
        union {
            struct {
                bool am_pm      : 1;    // PM indication flag
                uint8_t m_12h   : 1;    // hour (tens digit) in 12h mode in BCD
            } __attribute__((__packed__));
            uint8_t m_24h       : 2;    // hour (tens digit) in 24h mode in BCD
        } hour_tens;
        uint8_t                 : 2;    // unused
    } __attribute__((__packed__));
    uint8_t raw;
} hour_reg_t;

/* Day timekeeping register (address 0x06h) */
typedef union {
    struct {
        uint8_t day_units  : 4;    // day (units digit) in BCD
        uint8_t day_tens   : 2;    // day (tens digit) in BCD
        uint8_t            : 2;    // unused
    } __attribute__((__packed__));
    uint8_t raw;
} day_reg_t;

/* Weekday timekeeping register (address 0x07h) */
typedef union {
    struct {
        enum {
            SUN, MON, TUE, WED, THU, FRI, SAT
        } weekday   : 3;    // weekday as enum (in BCD)
        uint8_t     : 5;    // unused
    } __attribute__((__packed__));
    uint8_t raw;
} wday_reg_t;

/* Month timekeeping register (address 0x08h) */
typedef union {
    struct {
        uint8_t month_units : 4;    // month (units digit) in BCD
        uint8_t month_tens  : 1;    // month (tens digit) in BCD
        uint8_t             : 3;    // unused
    } __attribute__((__packed__));
    uint8_t raw;
} month_reg_t;

/* Year timekeeping register (address 0x09h) */
typedef union {
    struct {
        uint8_t year_units : 4;    // year (units digit) in BCD
        uint8_t year_tens  : 4;    // year (tens digit) in BCD
    } __attribute__((__packed__));
    uint8_t raw;
} year_reg_t;

/* Second alarm register (address 0x0Ah) */
typedef uint8_t sec_alm_reg_t;

/* Minute alarm register (address 0x0Bh) */
typedef uint8_t min_alm_reg_t;

/* Hour alarm register (address 0x0Ch) */
typedef uint8_t hour_alm_reg_t;

/* Day alarm register (address 0x0Dh) */
typedef uint8_t day_alm_reg_t;

/* Weekday alarm register (address 0x0Eh) */
typedef uint8_t wday_alm_reg_t;

/* CLKOUT control register (address 0x0Fh) */
typedef union {
    struct {
        uint8_t cof : 3;    // CLKOUT frequency control
        uint8_t     : 2;    // unused
        bool otpr   : 1;    // OTP calibration refresh control
        uint8_t tcr : 2;    // temperature measurement period control
    } __attribute__((__packed__));
    uint8_t raw;
} clkout_reg_t;

/* Watchdog timer control register (address 0x10h) */
typedef uint8_t wdt_ctl_reg_t;

/* Watchdog timer value register (address 0x11h) */
typedef uint8_t wdt_val_reg_t;

/* Timestamp control register (address 0x12h) */
typedef uint8_t timestp_ctl_reg_t;

/* Timestamp second register (address 0x13h) */
typedef uint8_t timestp_sec_reg_t;

/* Timestamp minute register (address 0x14h) */
typedef uint8_t timestp_min_reg_t;

/* Timestamp hour register (address 0x15h) */
typedef uint8_t timestp_hour_reg_t;

/* Timestamp day register (address 0x16h) */
typedef uint8_t timestp_day_reg_t;

/* Timestamp month register (address 0x17h) */
typedef uint8_t timestp_month_reg_t;

/* Timestamp year register (address 0x18h) */
typedef uint8_t timestp_year_reg_t;

/* Crystal aging compensation register (address 0x19h) */
typedef union {
    struct {
        uint8_t ao  : 4;    // Aging compensation value
        uint8_t     : 4;    // unused
    } __attribute__((__packed__));
    uint8_t raw;
} xtal_comp_reg_t;

/* RAM address MSB register (address 0x1Ah) */
typedef uint8_t ram_addr_msb_reg_t;

/* RAM address LSB register (address 0x1Bh) */
typedef uint8_t ram_addr_lsb_reg_t;

/* RAM write command register (address 0x1Ch) */
typedef uint8_t ram_wr_cmd_reg_t;

/* RAM read command register (address 0x1Dh) */
typedef uint8_t ram_rd_cmd_reg_t;

typedef struct {
    ctl_1_reg_t ctl_1_reg;                  // 0x00h
    ctl_2_reg_t ctl_2_reg;                  // 0x01h
    ctl_3_reg_t ctl_3_reg;                  // 0x02h
    sec_reg_t sec_reg;                      // 0x03h
    min_reg_t min_reg;                      // 0x04h
    hour_reg_t hour_reg;                    // 0x05h
    day_reg_t day_reg;                      // 0x06h
    wday_reg_t wday_reg;                    // 0x07h
    month_reg_t month_reg;                  // 0x08h
    year_reg_t year_reg;                    // 0x09h
    sec_alm_reg_t sec_alm_reg;              // 0x0Ah
    min_alm_reg_t min_alm_reg;              // 0x0Bh
    hour_alm_reg_t hour_alm_reg;            // 0x0Ch
    day_alm_reg_t day_alm_reg;              // 0x0Dh
    wday_alm_reg_t wday_alm_reg;            // 0x0Eh
    clkout_reg_t clkout_reg;                // 0x0Fh
    wdt_ctl_reg_t wdt_ctl_reg;              // 0x10h
    wdt_val_reg_t wdt_val_reg;              // 0x11h
    timestp_ctl_reg_t timestp_ctl_reg;      // 0x12h
    timestp_sec_reg_t timestp_sec_reg;      // 0x13h
    timestp_min_reg_t timestp_min_reg;      // 0x14h
    timestp_hour_reg_t timestp_hour_reg;    // 0x15h
    timestp_day_reg_t timestp_day_reg;      // 0x16h
    timestp_month_reg_t timestp_month_reg;  // 0x17h
    timestp_year_reg_t timestp_year_reg;    // 0x18h
    xtal_comp_reg_t xtal_comp_reg;          // 0x19h
    ram_addr_msb_reg_t ram_addr_msb_reg;    // 0x1Ah
    ram_addr_lsb_reg_t ram_addr_lsb_reg;    // 0x1Bh
    ram_wr_cmd_reg_t ram_wr_cmd_reg;        // 0x1Ch
    ram_rd_cmd_reg_t ram_rd_cmd_reg;        // 0x1Dh
} regmap_t;

uint8_t pcf2127_init(void);
uint8_t pcf2127_refresh_otp(void);
//uint8_t pcf2127_get_datetime(uint8_t (* const datetime)[DATETIME_SIZE]);
//uint8_t pcf2127_set_datetime(const uint8_t (* const datetime)[DATETIME_SIZE]);
uint8_t pcf2127_get_datetime(DatetimeBcd *const datetime);
uint8_t pcf2127_set_datetime(const DatetimeBcd *const datetime);

#endif /* PCF2127_H_ */