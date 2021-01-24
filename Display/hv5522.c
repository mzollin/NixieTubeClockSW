/*
 * Copyright (C) 2021 Marco Zollinger <marco@freelabs.space>
 * GNU General Public License Version 3
 */

#include "hv5522.h"

#include <assert.h>
#include <avr/io.h>

static void hv5522_send_frame(const uint8_t (* const data)[8])
{
    uint8_t i;
    
    assert(data != 0);          // check if not a nullptr
    assert((*data) != 0);       // check if not ptr to a nullptr
    assert(SPCR & (1 << SPE));  // check if SPI is enabled
    
    PORTB |= (1 << SS); // latch the HV5522 output while sending 8 bytes
    for(i = 0; i < 8; ++i)
    {
        SPDR = ~(*((*data) + i));
        assert(!(SPSR & (1 << WCOL)));  // check for write collision
        while(!(SPSR & (1 << SPIF)));   // wait for transmission to finish
    }
    PORTB &=~ (1 << SS);    
}

static uint16_t hv5522_bin_to_dec(uint8_t binary)
{
    uint16_t decimal;
    
    assert(binary <= 9);    // check for valid digit number
    if (binary == 0)
    {
        binary = 10;
    }
    decimal = (1 << (binary - 1));
    return decimal;
}

void hv5522_clear(void)
{
    uint8_t zero[8] = {0};

    hv5522_send_frame(&zero);
}

void hv5522_init(void)
{
    DDRB |= (1 << SS) | (1 << MOSI) | (1 << SCK);   // set interface pins to output
    PORTB |= (1 << MISO);   // unused -> pullup
    /* TODO try faster interface speeds */
    SPCR |= (1 << MSTR) | (1 << SPE) | (1 << SPR1); // enable SPI master
    hv5522_clear();
}

void hv5522_show_digits(struct digits *d)
{
    uint8_t data[8] = {0};

    data[7]  = hv5522_bin_to_dec(d->sixth);
    data[6]  = (hv5522_bin_to_dec(d->sixth) >> 8);
    data[6] |= (hv5522_bin_to_dec(d->fifth) << 2);
    data[5]  = (hv5522_bin_to_dec(d->fifth) >> 6);

    data[5] |= (hv5522_bin_to_dec(d->fourth) << 6);
    data[4]  = (hv5522_bin_to_dec(d->fourth) >> 2);
    data[3]  = hv5522_bin_to_dec(d->third);
    data[2]  = (hv5522_bin_to_dec(d->third) >> 8);

    data[2] |= (hv5522_bin_to_dec(d->second) << 2);
    data[1]  = (hv5522_bin_to_dec(d->second) >> 6);
    data[1] |= (hv5522_bin_to_dec(d->first) << 6);
    data[0]  = (hv5522_bin_to_dec(d->first) >> 2);

    hv5522_send_frame(&data);
}
