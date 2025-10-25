#ifndef BUTTONS_H
#define BUTTONS_H

#include "gpio.h"
#include "event.h"
#include "log.h"

#define BUTTON_BOUND_TIMEOUT 200

void Buttons_init(void);
void LED_init(void);

extern uint16_t bound_timer;

#endif