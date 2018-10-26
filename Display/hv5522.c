// Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>
// GNU General Public License Version 3

#define F_CPU 11059200UL

#include "hv5522.h"
#include <avr/io.h>
#include <stdlib.h>
#include <assert.h>
#include <util/delay.h>

void hv5522_init(void)
{
    uint8_t zero[8] = {0};
    
    DDRB |= (1<<SS) | (1<<MOSI) | (1<<SCK);    // set interface pins to output
    PORTB |= (1<<MISO);    // unused -> pullup
    // TODO try faster interface speeds
    SPCR |= (1<<MSTR) | (1<<SPE) | (1<<SPR1);    // enable SPI master
    hv5522_SendFrame(&zero);    // clear all bits in both HV5522
}

void hv5522_SendFrame(const uint8_t (* const data)[8]) {
    uint8_t i;
    
    assert(data != 0);            // check if not a nullptr
    assert((*data) != 0);        // check if not ptr to a nullptr
    assert(SPCR & (1<<SPE));    // check if SPI is enabled
    
    PORTB |= (1<<SS);            // latch the HV5522 output while sending 8 bytes
    for(i = 0; i < 8; ++i) {
        SPDR = ~(*((*data) + i));
        assert(!(SPSR & (1<<WCOL)));    // check for write collision
        while(!(SPSR & (1<<SPIF)));        // wait for transmission to finish
    }
    PORTB &=~ (1<<SS);    
}

uint16_t hv5522_Bin2Dec(uint8_t binary)
{
    uint16_t decimal;
    
    assert(binary <= 9);    // check for valid digit number
    
    if(!binary) binary = 10;
    decimal = (1<<(binary - 1));
    
    return decimal;
}

/*
void hv5522_SendDateTime(uint8_t x100, uint8_t x10, uint8_t x1, uint8_t is_time) // send data to display either time or date
{
    
    // TODO: roll only the digits that change?
    // FIXME: disable rolling while setting the time
    
    div_t bcd;
    uint8_t data[8] = {0};
    uint8_t x1rem = 0;
    uint8_t x1quot = 0;
    uint8_t x10rem = 0;
    uint8_t x10quot = 0;
    uint8_t x100rem = 0;
    uint8_t x100quot = 0;
    static uint8_t lastx1rem = 0;
    static uint8_t lastx1quot = 0;
    static uint8_t lastx10rem = 0;
    static uint8_t lastx10quot = 0;
    static uint8_t lastx100rem = 0;
    static uint8_t lastx100quot = 0;
    static uint8_t was_time = 1;
    static uint8_t lastx10 = 0;
    static uint8_t lastx100 = 0;
    uint8_t count = 63;
    uint8_t i = 10;
    
    if((is_time == was_time) && (x10 == lastx10) && (x100 == lastx100))    // normal second update
    {
        // display mode unchanged
        bcd = div(x1, 10);
        data[7]  = hv5522_Bin2Dec(bcd.rem);
        data[6]  = (hv5522_Bin2Dec(bcd.rem) >> 8);
        data[6] |= (hv5522_Bin2Dec(bcd.quot) << 2);
        data[5]  = (hv5522_Bin2Dec(bcd.quot) >> 6);
        lastx1rem = bcd.rem;
        lastx1quot = bcd.quot;
        bcd = div(x10, 10);
        data[5] |= (hv5522_Bin2Dec(bcd.rem) << 6);
        data[4]  = (hv5522_Bin2Dec(bcd.rem) >> 2);
        data[3]  = hv5522_Bin2Dec(bcd.quot);
        data[2]  = (hv5522_Bin2Dec(bcd.quot) >> 8);
        lastx10rem = bcd.rem;
        lastx10quot = bcd.quot;
        bcd = div(x100, 10);
        data[2] |= (hv5522_Bin2Dec(bcd.rem) << 2);
        data[1]  = (hv5522_Bin2Dec(bcd.rem) >> 6);
        data[1] |= (hv5522_Bin2Dec(bcd.quot) << 6);
        data[0]  = (hv5522_Bin2Dec(bcd.quot) >> 2);
        lastx100rem = bcd.rem;
        lastx100quot = bcd.quot;
    
        hv5522_SendFrame(&data);
    }
    else if((is_time == was_time) && (x100 == lastx100))    // minute change
    {
        count = 3;
        // display mode has changed
        bcd = div(x1, 10);
        x1rem = bcd.rem;
        x1quot = bcd.quot;
        bcd = div(x10, 10);
        x10rem = bcd.rem;
        x10quot = bcd.quot;
        bcd = div(x100, 10);
        x100rem = bcd.rem;
        x100quot = bcd.quot;
        
        do
        {
            if((lastx1rem != x1rem) || i)
            {
                lastx1rem = (lastx1rem+1)%10;
            }
            else count &=~ (1<<0);
            if((lastx1quot != x1quot) || i)
            {
                lastx1quot = (lastx1quot+1)%10;
            }
            else count &=~ (1<<1);
            
            if(i) i--;
            
            data[7]  = hv5522_Bin2Dec(lastx1rem);
            data[6]  = (hv5522_Bin2Dec(lastx1rem) >> 8);
            data[6] |= (hv5522_Bin2Dec(lastx1quot) << 2);
            data[5]  = (hv5522_Bin2Dec(lastx1quot) >> 6);

            data[5] |= (hv5522_Bin2Dec(x10rem) << 6);
            data[4]  = (hv5522_Bin2Dec(x10rem) >> 2);
            data[3]  = hv5522_Bin2Dec(x10quot);
            data[2]  = (hv5522_Bin2Dec(x10quot) >> 8);

            data[2] |= (hv5522_Bin2Dec(x100rem) << 2);
            data[1]  = (hv5522_Bin2Dec(x100rem) >> 6);
            data[1] |= (hv5522_Bin2Dec(x100quot) << 6);
            data[0]  = (hv5522_Bin2Dec(x100quot) >> 2);
    
            hv5522_SendFrame(&data);    
            _delay_ms(30);    
        }while(count);            
    }
    else if(is_time == was_time)    // hour change
    {
        count = 15;
        // display mode has changed
        bcd = div(x1, 10);
        x1rem = bcd.rem;
        x1quot = bcd.quot;
        bcd = div(x10, 10);
        x10rem = bcd.rem;
        x10quot = bcd.quot;
        bcd = div(x100, 10);
        x100rem = bcd.rem;
        x100quot = bcd.quot;
        
        do
        {
            if((lastx1rem != x1rem) || i)
            {
                lastx1rem = (lastx1rem+1)%10;
            }
            else count &=~ (1<<0);
            if((lastx1quot != x1quot) || i)
            {
                lastx1quot = (lastx1quot+1)%10;
            }
            else count &=~ (1<<1);
            if((lastx10rem != x10rem) || i)
            {
                lastx10rem = (lastx10rem+1)%10;
            }
            else count &=~ (1<<2);
            if((lastx10quot != x10quot) || i)
            {
                lastx10quot = (lastx10quot+1)%10;
            }
            else count &=~ (1<<3);
            
            if(i) i--;
            
            data[7]  = hv5522_Bin2Dec(lastx1rem);
            data[6]  = (hv5522_Bin2Dec(lastx1rem) >> 8);
            data[6] |= (hv5522_Bin2Dec(lastx1quot) << 2);
            data[5]  = (hv5522_Bin2Dec(lastx1quot) >> 6);

            data[5] |= (hv5522_Bin2Dec(lastx10rem) << 6);
            data[4]  = (hv5522_Bin2Dec(lastx10rem) >> 2);
            data[3]  = hv5522_Bin2Dec(lastx10quot);
            data[2]  = (hv5522_Bin2Dec(lastx10quot) >> 8);

            data[2] |= (hv5522_Bin2Dec(x100rem) << 2);
            data[1]  = (hv5522_Bin2Dec(x100rem) >> 6);
            data[1] |= (hv5522_Bin2Dec(x100quot) << 6);
            data[0]  = (hv5522_Bin2Dec(x100quot) >> 2);
    
            hv5522_SendFrame(&data);    
            _delay_ms(30);    
        }while(count);            
    }
    else    // change time/date mode
    {
        count = 63;
        // display mode has changed
        bcd = div(x1, 10);
        x1rem = bcd.rem;
        x1quot = bcd.quot;
        bcd = div(x10, 10);
        x10rem = bcd.rem;
        x10quot = bcd.quot;
        bcd = div(x100, 10);
        x100rem = bcd.rem;
        x100quot = bcd.quot;
        
        do
        {
            if((lastx1rem != x1rem) || i)
            {
                lastx1rem = (lastx1rem+1)%10;
            }
            else count &=~ (1<<0);
            if((lastx1quot != x1quot) || i)
            {
                lastx1quot = (lastx1quot+1)%10;
            }
            else count &=~ (1<<1);
            if((lastx10rem != x10rem) || i)
            {
                lastx10rem = (lastx10rem+1)%10;
            }
            else count &=~ (1<<2);
            if((lastx10quot != x10quot) || i)
            {
                lastx10quot = (lastx10quot+1)%10;
            }
            else count &=~ (1<<3);
            if((lastx100rem != x100rem) || i)
            {
                lastx100rem = (lastx100rem+1)%10;
            }
            else count &=~ (1<<4);
            if((lastx100quot != x100quot) || i)
            {
                lastx100quot = (lastx100quot+1)%10;
            }    
            else count &=~ (1<<5);
            
            if(i) i--;
            
            data[7]  = hv5522_Bin2Dec(lastx1rem);
            data[6]  = (hv5522_Bin2Dec(lastx1rem) >> 8);
            data[6] |= (hv5522_Bin2Dec(lastx1quot) << 2);
            data[5]  = (hv5522_Bin2Dec(lastx1quot) >> 6);

            data[5] |= (hv5522_Bin2Dec(lastx10rem) << 6);
            data[4]  = (hv5522_Bin2Dec(lastx10rem) >> 2);
            data[3]  = hv5522_Bin2Dec(lastx10quot);
            data[2]  = (hv5522_Bin2Dec(lastx10quot) >> 8);

            data[2] |= (hv5522_Bin2Dec(lastx100rem) << 2);
            data[1]  = (hv5522_Bin2Dec(lastx100rem) >> 6);
            data[1] |= (hv5522_Bin2Dec(lastx100quot) << 6);
            data[0]  = (hv5522_Bin2Dec(lastx100quot) >> 2);
    
            hv5522_SendFrame(&data);    
            _delay_ms(30);    
        }while(count);            
    }
    was_time = is_time;
    lastx10 = x10;    
    lastx100 = x100;
}
*/

/*
void hv5522_DisplayDate(uint8_t day, uint8_t month, uint8_t year)            // display date
{
    assert((day >= 1) && (day <= 31));
    assert((month >= 1) && (month <= 12));    // basic check for a valid date
    
    hv5522_SendDateTime(day, month, year, 0);
}    

void hv5522_DisplayTime(uint8_t hour, uint8_t minute, uint8_t second)        // display time
{
    assert(hour < 24);
    assert(minute < 60);
    assert(second < 60);    // basic check for a valid time
    
    hv5522_SendDateTime(hour, minute, second, 1);
}
*/

void hv5522_SendDigits(uint8_t ll, uint8_t rl, uint8_t lm, uint8_t rm, uint8_t lr, uint8_t rr) {
    uint8_t data[8] = {0};

    data[7]  = hv5522_Bin2Dec(rr);
    data[6]  = (hv5522_Bin2Dec(rr) >> 8);
    data[6] |= (hv5522_Bin2Dec(lr) << 2);
    data[5]  = (hv5522_Bin2Dec(lr) >> 6);

    data[5] |= (hv5522_Bin2Dec(rm) << 6);
    data[4]  = (hv5522_Bin2Dec(rm) >> 2);
    data[3]  = hv5522_Bin2Dec(lm);
    data[2]  = (hv5522_Bin2Dec(lm) >> 8);

    data[2] |= (hv5522_Bin2Dec(rl) << 2);
    data[1]  = (hv5522_Bin2Dec(rl) >> 6);
    data[1] |= (hv5522_Bin2Dec(ll) << 6);
    data[0]  = (hv5522_Bin2Dec(ll) >> 2);

    hv5522_SendFrame(&data);
}