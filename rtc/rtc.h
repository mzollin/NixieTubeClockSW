/*
 * Copyright (C) 2021 Marco Zollinger <marco@freelabs.space>
 * GNU General Public License Version 3
 */

#ifndef RTC_H_
#define RTC_H_

#include "../datetimebcd_type.h"

#define RTC_CLK PD2    // INT0
#define RTC_INT PD3    // INT1

void init_rtc(void);
DatetimeBcd get_datetime(void);
void set_datetime(DatetimeBcd datetime);

#endif /* RTC_H_ */