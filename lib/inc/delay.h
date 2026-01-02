#ifndef DELAY_H
#define DELAY_H

#include "stm32f407xx.h"

#define AHB1_FREQ_HZ  84000000
#define SYSTICK_TIMER_PERIOD_US  1
#define SYSTICK_TIMER_CONST     ((AHB1_FREQ_HZ * (SYSTICK_TIMER_PERIOD_US))/ 1000000) - 1

#define LED_BLINK_300ms   300
extern uint16_t us_counter;
extern uint16_t ms_counter;
extern uint16_t sec_counter;
void timer_counter(void);


void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_sec(uint32_t sec);
void delay_us_tim10(uint16_t us_tim10);

#endif