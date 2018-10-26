// Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>

#include "hardware.h"
#include <avr/io.h>

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

void check_encoder(void) {

}