#ifndef DATETIME_TYPE_H_
#define DATETIME_TYPE_H_

#include <avr/io.h>
#include <stdbool.h>

typedef union {
    struct {
        uint8_t seconds_unit : 4;
        uint8_t seconds_tens : 3;
        bool integrity_fail : 1;
    } __attribute__((__packed__)) fld;
    uint8_t all;
} DatetimeBcdSecond;

typedef union {
    struct {
        uint8_t minutes_unit : 4;
        uint8_t minutes_tens : 3;
    } __attribute__((__packed__)) fld;
    uint8_t all;
} DatetimeBcdMinute;

typedef union {
    struct {
        uint8_t hours_unit : 4;
        uint8_t hours_tens : 2;
    } __attribute__((__packed__)) fld;
    uint8_t all;
} DatetimeBcdHour;

typedef union {
    struct {
        uint8_t days_unit : 4;
        uint8_t days_tens : 2;
    } __attribute__((__packed__)) fld;
    uint8_t all;
} DatetimeBcdDay;

typedef union {
    struct {
        uint8_t weekdays : 3;
    } __attribute__((__packed__)) fld;
    uint8_t all;
} DatetimeBcdWeekday;

typedef union {
    struct {
        uint8_t months_unit : 4;
        uint8_t months_tens : 1;
    } __attribute__((__packed__)) fld;
    uint8_t all;
} DatetimeBcdMonth;

typedef union {
    struct {
        uint8_t years_unit : 4;
        uint8_t years_tens : 4;
    } __attribute__((__packed__)) fld;
    uint8_t all;
} DatetimeBcdYear;

typedef struct {
    DatetimeBcdSecond seconds;
    DatetimeBcdMinute minutes;
    DatetimeBcdHour hours;
    DatetimeBcdDay days;
    DatetimeBcdWeekday weekdays;
    DatetimeBcdMonth months;
    DatetimeBcdYear years;
} DatetimeBcd;

#endif /* DATETIME_TYPE_H_ */