/*
 * Copyright (C) 2021 Marco Zollinger <marco@freelabs.space>
 * GNU General Public License Version 3
 */

#include "hardware.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

static volatile uint16_t g_rtc_ticks = 0;
volatile uint8_t g_rtc_seconds = 0;

// FIXME: better solution?
volatile int8_t g_deltaEnc;
static int8_t g_lastEnc;    // encoder variables

void init_io(void) {
    // enable pull-up on PIR sensor input
    //PORTC |= (1<<PIR); // pullup

    // enable pull-ups on encoder inputs
    PORTD |= (1<<ENC_R) | (1<<ENC_L) | (1<<ENC_P);
    
    // enable pull-ups on unused pins
    PORTB |= (1<<PWM);
    PORTC |= (1<<EXP_0) | (1<<EXP_1);
    PORTD |= (1<<GPS_TXD) | (1<<GPS_RXD) | (1<<GPS_INT);


    int8_t new = 0;

    // initialize the encoder
    if(PIND & (1<<ENC_R)) new = 3;
    if(PIND & (1<<ENC_L)) new ^= 1; // convert gray to binary
    g_lastEnc = new;                // power on state
    g_deltaEnc = 0;
}

Encoder check_encoder(void) {
    Encoder encoder;

    encoder.left_counts = 0;
    encoder.right_counts = 0;
    int8_t enc = getEncode();
    if (enc > 0) {
        encoder.right_counts = 1;
    }
    else if (enc < 0) {
        encoder.left_counts = 1;
    }

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

int8_t getEncode(void)
{
    int8_t val;
    
    cli();
    val = g_deltaEnc;
    g_deltaEnc = val & 3;
    sei();
    return val >> 2;    // counts since last call
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

    int8_t diff;
    int8_t new = 0;

    if(PIND & (1<<ENC_R)) new = 3;
    if(PIND & (1<<ENC_L)) new ^= 1;     // convert gray to binary
    diff = g_lastEnc - new;             // difference last - new
    if( diff & 1 )                      // bit 0 = value (1)
    {
        g_lastEnc = new;                // store new as next last
        g_deltaEnc += (diff & 2) - 1;   // bit 1 = direction (+/-)
    }
}