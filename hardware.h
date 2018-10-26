// Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>
// GNU General Public License Version 3

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <avr/io.h>
#include <stdbool.h>

#define PWM PB1

#define LDR PC0

#define PIR PC1

#define EXP_0 PC2
#define EXP_1 PC3

#define GPS_TXD PD0
#define GPS_RXD PD1
#define GPS_INT PD4

#define ENC_R PD6
#define ENC_L PD5
#define ENC_P PD7

enum { BOUNCE_TIMEOUT = 20 };

typedef struct {
    uint8_t left_counts;
    uint8_t right_counts;
    bool center_press;
} Encoder;

void init_io(void);
Encoder check_encoder(void);
void wait_encoder_click(void);

#endif /* HARDWARE_H_ */