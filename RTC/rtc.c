// Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>
// GNU General Public License Version 3

#include "rtc.h"
#include "pcf2127.h"
#include <avr/interrupt.h>

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
    DatetimeBcd datetime;
    while(pcf2127_get_datetime(&datetime)) {

    }

    /*
    uint8_t error = 1;
    do {
        error = pcf2127_get_datetime(&data);
    } while (error);
    */

    return datetime;
}

void set_datetime(DatetimeBcd datetime) {

}