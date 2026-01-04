#ifndef DELAY_H
#define DELAY_H

#include "stm32f4xx.h"

#define AHB1_FREQ_HZ				84000000
#define SYSTICK_TIMER_PERIOD_US		1	
#define SYSTICK_TIMER_CONST			( ( ( AHB1_FREQ_HZ * ( SYSTICK_TIMER_PERIOD_US ) ) / 1000000 ) - 1 )

#define LED_BLINK_300ms				300

// ---- Functions for SysTick_Handler(void) period = 1 us----
void timer_counter(uint16_t *btn_ms_counter);



void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_sec(uint32_t sec);




#endif
