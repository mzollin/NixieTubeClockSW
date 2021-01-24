/*
 * Copyright (C) 2021 Marco Zollinger <marco@freelabs.space>
 * GNU General Public License Version 3
 */

#ifndef HV5522_H_
#define HV5522_H_

#include <avr/io.h>

#define SS      PB2
#define MOSI    PB3
#define MISO    PB4
#define SCK     PB5

/*
 * All six digits of the nixie tube display, numbered from left to right.
 */
struct digits
{
    uint8_t first;  // leftmost nixie
    uint8_t second;
    uint8_t third;
    uint8_t fourth;
    uint8_t fifth;
    uint8_t sixth;  // rightmost nixie
};

/*
 * Initialize the SPI interface and clear (blank display) the HV5522 driver.
 */
void hv5522_init(void);

/*
 * Clear (blank display) the HV5522 driver.
 */
void hv5522_clear(void);

/*
 * Send digit data to the HV5522 driver to display on the nixie tubes.
 */
void hv5522_show_digits(struct digits *d);

#endif /* HV5522_H_ */
