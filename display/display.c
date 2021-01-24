/*
 * Copyright (C) 2021 Marco Zollinger <marco@freelabs.space>
 * GNU General Public License Version 3
 */

#include "display.h"
#include "hv5522.h"
#include <avr/io.h>


void init_display(void) {
    // set boost converter enable pin to output and disable
    DDRB |= (1<<BOOST_EN);
    PORTB |= (1<<BOOST_EN);

    hv5522_init();
}

void enable_display(void) {
    PORTB &=~ (1<<BOOST_EN);
}

void disable_display(void) {
    PORTB |= (1<<BOOST_EN); 
}

void display_datetime(DatetimeBcd datetime)
{
    struct digits d = {
        .first = datetime.hours.tens,
        .second = datetime.hours.units,
        .third = datetime.minutes.tens,
        .fourth = datetime.minutes.units,
        .fifth = datetime.seconds.tens,
        .sixth = datetime.seconds.units,
    };

    enable_display();
    hv5522_show_digits(&d);
}