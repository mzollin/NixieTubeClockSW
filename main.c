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
        wait_encoder_click();
        wait_encoder_click();
        wait_encoder_click();
        wait_encoder_click();
        wait_encoder_click();
        set_datetime(datetime);
    }
}