#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "datetime_type.h"

#define BOOST_EN PB0

void init_display(void);
void enable_display(void);
void display_datetime(Datetime datetime);

#endif /* DISPLAY_H_ */