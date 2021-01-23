/*
Copyright (C) 2018 Marco Zollinger <marco@freelabs.space>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define F_CPU 11059200UL

#include "hardware.h"
#include "RTC/rtc.h"
#include "Display/display.h"
#include <stdbool.h>
#include <util/delay.h>

void check_settime(void);
void secure_increase(volatile uint8_t *ptr, uint8_t min, uint8_t max, uint8_t rollover);
void secure_decrease(volatile uint8_t *ptr, uint8_t min, uint8_t max, uint8_t rollover);

extern uint8_t g_rtc_seconds;

int main(void) {
    init_io();
    init_rtc();
    init_display();
    while (true) {
        check_settime();
        display_datetime(get_datetime());
        _delay_ms(10);
    }
}

void check_settime(void) {
    if (check_encoder().center_press) {
        DatetimeBcd datetime = get_datetime();


        // FIXME magic number
        for (uint8_t i = 0; i < 1; ++i) {

            while(check_encoder().center_press);
            while(!check_encoder().center_press) {
                if (check_encoder().left_counts) {
                    datetime.hours.tens--;
                }
                else if (check_encoder().right_counts) {
                    datetime.hours.tens++;
                }
                display_datetime(datetime);
            }
            while(check_encoder().center_press);

            while(check_encoder().center_press);
            while(!check_encoder().center_press) {
                if (check_encoder().left_counts) {
                    datetime.hours.units--;
                }
                else if (check_encoder().right_counts) {
                    datetime.hours.units++;
                }
                display_datetime(datetime);
            }
            while(check_encoder().center_press);

            while(check_encoder().center_press);
            while(!check_encoder().center_press) {
                if (check_encoder().left_counts) {
                    datetime.minutes.tens--;
                }
                else if (check_encoder().right_counts) {
                    datetime.minutes.tens++;
                }
                display_datetime(datetime);
            }
            while(check_encoder().center_press);

            while(check_encoder().center_press);
            while(!check_encoder().center_press) {
                if (check_encoder().left_counts) {
                    datetime.minutes.units--;
                }
                else if (check_encoder().right_counts) {
                    datetime.minutes.units++;
                }
                display_datetime(datetime);
            }
            while(check_encoder().center_press);

            while(check_encoder().center_press);
            while(!check_encoder().center_press) {
                if (check_encoder().left_counts) {
                    datetime.seconds.tens--;
                }
                else if (check_encoder().right_counts) {
                    datetime.seconds.tens++;
                }
                display_datetime(datetime);
            }
            while(check_encoder().center_press);

            while(check_encoder().center_press);
            while(!check_encoder().center_press) {
                if (check_encoder().left_counts) {
                    datetime.seconds.units--;
                }
                else if (check_encoder().right_counts) {
                    datetime.seconds.units++;
                }
                display_datetime(datetime);
            }
            while(check_encoder().center_press);

        }


        set_datetime(datetime);
    }
}

void secure_increase(volatile uint8_t *ptr, uint8_t min, uint8_t max, uint8_t rollover)
{
    if(*ptr < max) (*ptr)++;
    else if(rollover) *ptr = min;
}

void secure_decrease(volatile uint8_t *ptr, uint8_t min, uint8_t max, uint8_t rollover)
{
    if(*ptr > min) (*ptr)--;
    else if(rollover) *ptr = max;
}