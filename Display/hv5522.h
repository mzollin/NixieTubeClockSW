#ifndef HV5522_H_
#define HV5522_H_

#include <avr/io.h>

#define SS PB2
#define MOSI PB3
#define MISO PB4
#define SCK PB5

void hv5522_init(void);
void hv5522_SendFrame(const uint8_t (* const data)[8]);
uint16_t hv5522_Bin2Dec(uint8_t binary);
void hv5522_DisplayTime(uint8_t hour, uint8_t minute, uint8_t second);
void hv5522_DisplayDate(uint8_t day, uint8_t month, uint8_t year);
void hv5522_SendDateTime(uint8_t x100, uint8_t x10, uint8_t x1, uint8_t is_time);

void hv5522_SendTime(uint8_t ll, uint8_t rl, uint8_t lm, uint8_t rm, uint8_t lr, uint8_t rr);

#endif /* HV5522_H_ */