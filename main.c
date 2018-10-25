#define F_CPU 11059200UL

#include "hardware.h"
#include "RTC/rtc.h"
#include "Display/display.h"
#include <stdbool.h>
#include <util/delay.h>

int main(void) {
    init_io();
    init_rtc();
    init_display();
    while (true) {
        display_datetime(get_datetime());
        _delay_ms(100);
        check_encoder();
    }
}