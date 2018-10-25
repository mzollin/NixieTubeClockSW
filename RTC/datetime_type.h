#ifndef DATETIME_TYPE_H_
#define DATETIME_TYPE_H_

#include <avr/io.h>

typedef struct {
    uint8_t tens_hours;
    uint8_t unit_hours;
    uint8_t tens_minutes;
    uint8_t unit_minutes;
    uint8_t tens_seconds;
    uint8_t unit_seconds;
    uint8_t tens_days;
    uint8_t unit_days;
    uint8_t tens_months;
    uint8_t unit_months;
    uint8_t tens_years;
    uint8_t unit_years;
} Datetimebcd;

#endif /* DATETIME_TYPE_H_ */