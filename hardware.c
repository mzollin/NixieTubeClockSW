// Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>
// GNU General Public License Version 3

#include "hardware.h"
#include <avr/io.h>
#include <util/delay.h>

void init_io(void) {
    // enable pull-up on PIR sensor input
    //PORTC |= (1<<PIR); // pullup

    // enable pull-ups on encoder inputs
    PORTD |= (1<<ENC_R) | (1<<ENC_L) | (1<<ENC_P);
    
    // enable pull-ups on unused pins
    PORTB |= (1<<PWM);
    PORTC |= (1<<EXP_0) | (1<<EXP_1);
    PORTD |= (1<<GPS_TXD) | (1<<GPS_RXD) | (1<<GPS_INT);
}

Encoder check_encoder(void) {
    Encoder encoder;
    encoder.center_press = true;
    for (uint8_t i = 0; i < BOUNCE_TIMEOUT; ++i) {
        if (PIND & (1<<ENC_P)) {
            encoder.center_press = false;
            _delay_ms(1);
        }
    }
    return encoder;
}

void wait_encoder_click(void) {
    while(check_encoder().center_press);
    while(!check_encoder().center_press);
    while(check_encoder().center_press);
}