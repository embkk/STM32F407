#ifndef BUTTONS_H
#define BUTTONS_H

#include "gpio.h"
#include "event.h"
#include "log.h"

#define BTN_PRESS_COUNT 4
#define BTN_CHECK_MS 20

extern uint8_t btn_state[3];

void Buttons_init(void);
void LED_init(void);
void Buttons_check(void);

#endif