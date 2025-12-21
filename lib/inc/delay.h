#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

#define AHB1_FREQ_HZ              84000000
#define SYSTICK_TIMER_PERIOD_US   1
#define SYSTICK_TIMER_CONST       ( AHB1_FREQ_HZ * SYSTICK_TIMER_PERIOD_US / 1000 - 1 )

void timer_counter(void);

void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_sec(uint32_t sec);

#endif