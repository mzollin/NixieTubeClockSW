#ifndef RTC_H_
#define RTC_H_

#include "datetime_type.h"

#define RTC_CLK PD2	// INT0
#define RTC_INT PD3	// INT1

enum { TICKS_PER_SECOND = 1024 };

void init_rtc(void);
Datetime get_datetime(void);

#endif /* RTC_H_ */