/*
 * Copyright (C) 2021 Marco Zollinger <marco@freelabs.space>
 * GNU General Public License Version 3
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../datetimebcd_type.h"

#define BOOST_EN PB0

void init_display(void);
void enable_display(void);
void disable_display(void);
void display_datetime(DatetimeBcd datetime);

#endif /* DISPLAY_H_ */