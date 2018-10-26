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

void display_datetime(DatetimeBcd datetime) {
    enable_display();
    // FIXME: filter out integrity_fail flag
    hv5522_SendTime(datetime.hours.tens, datetime.hours.units, datetime.minutes.tens, datetime.minutes.units, datetime.seconds.tens, datetime.seconds.units);
}