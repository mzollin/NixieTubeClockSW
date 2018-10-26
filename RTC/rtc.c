// Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>

#include "rtc.h"
#include "pcf2127.h"
#include <avr/interrupt.h>

static volatile uint16_t g_rtc_ticks = 0;
static volatile uint8_t g_rtc_seconds = 0;

void init_rtc(void) {
    // enable pull-ups on RTC clock and interrupt inputs
    PORTD |= (1<<RTC_CLK) | (1<<RTC_INT);

    pcf2127_init();

    // enable INT0 interrupt and select rising-edge trigger
    EICRA |= (1<<ISC01) | (1<<ISC00);
    EIMSK |= (1<<INT0);

    // enable global interrupts
    sei();
}

DatetimeBcd get_datetime(void) {
    uint8_t data[7];

    while(pcf2127_get_datetime(&data)) {

    }

    /*
    uint8_t error = 1;
    do {
        error = pcf2127_get_datetime(&data);
    } while (error);
    */

    /*
    Datetime datetime;
    datetime.seconds = data[SECONDS_BYTE];
    datetime.minutes = data[MINUTES_BYTE];
    datetime.hours = data[HOURS_BYTE];
    datetime.days = data[DAYS_BYTE];
    datetime.months = data[MONTHS_BYTE];
    datetime.years = data[YEARS_BYTE];
    return datetime;
    */

    DatetimeBcd datetime;

    datetime.seconds.all = data[SECONDS_BYTE];
    datetime.minutes.all = data[MINUTES_BYTE];
    datetime.hours.all = data[HOURS_BYTE];

    datetime.days.all = data[DAYS_BYTE];
    datetime.months.all = data[MONTHS_BYTE];
    datetime.years.all = data[YEARS_BYTE];
    return datetime;
}

ISR(INT0_vect)
{
    if (g_rtc_seconds < UINT8_MAX) {
        ++g_rtc_ticks;
        if (g_rtc_ticks >= TICKS_PER_SECOND) {
            g_rtc_ticks -= TICKS_PER_SECOND;
            ++g_rtc_seconds;
        }
    }
}