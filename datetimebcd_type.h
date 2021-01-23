// Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>
// GNU General Public License Version 3

#ifndef DATETIME_TYPE_H_
#define DATETIME_TYPE_H_

#include <avr/io.h>
#include <stdbool.h>

typedef union {
    struct {
        uint8_t units : 4;
        uint8_t tens : 3;
        bool integrity_fail : 1;
    } __attribute__((__packed__));
    uint8_t all;
} DatetimeBcdSecond;

typedef union {
    struct {
        uint8_t units : 4;
        uint8_t tens : 3;
    } __attribute__((__packed__));
    uint8_t all;
} DatetimeBcdMinute;

typedef union {
    struct {
        uint8_t units : 4;
        uint8_t tens : 2;
    } __attribute__((__packed__));
    uint8_t all;
} DatetimeBcdHour;

typedef union {
    struct {
        uint8_t units : 4;
        uint8_t tens : 2;
    } __attribute__((__packed__));
    uint8_t all;
} DatetimeBcdDay;

typedef union {
    struct {
        uint8_t units : 3;
    } __attribute__((__packed__));
    uint8_t all;
} DatetimeBcdWeekday;

typedef union {
    struct {
        uint8_t units : 4;
        uint8_t tens : 1;
    } __attribute__((__packed__));
    uint8_t all;
} DatetimeBcdMonth;

typedef union {
    struct {
        uint8_t units : 4;
        uint8_t tens : 4;
    } __attribute__((__packed__));
    uint8_t all;
} DatetimeBcdYear;

typedef union {
    struct {
        DatetimeBcdSecond seconds;
        DatetimeBcdMinute minutes;
        DatetimeBcdHour hours;
        DatetimeBcdDay days;
        DatetimeBcdWeekday weekdays;
        DatetimeBcdMonth months;
        DatetimeBcdYear years;
    } __attribute__((__packed__));
    uint8_t all[7];
} DatetimeBcd;

#endif /* DATETIME_TYPE_H_ */