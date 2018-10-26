/*
Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>
*/

#ifndef HARDWARE_H_
#define HARDWARE_H_

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

void init_io(void);
void check_encoder(void);

#endif /* HARDWARE_H_ */