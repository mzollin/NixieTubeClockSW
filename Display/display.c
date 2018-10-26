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
    hv5522_SendTime(datetime.hours.fld.hours_tens, datetime.hours.fld.hours_unit, datetime.minutes.fld.minutes_tens, datetime.minutes.fld.minutes_unit, datetime.seconds.fld.seconds_tens, datetime.seconds.fld.seconds_unit);
}