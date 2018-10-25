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

void display_datetime(Datetime datetime) {
    enable_display();
    hv5522_SendTime(datetime.hours, datetime.minutes, datetime.seconds);
}