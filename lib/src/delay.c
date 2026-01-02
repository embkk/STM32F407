#include "delay.h"

uint32_t  delay_us;
uint32_t  delay_ms;
uint32_t  delay_sec;

  uint16_t us_counter;
  uint16_t ms_counter;
  uint16_t sec_counter;

void timer_counter(void) {
 
  
  delay_us++;
  if(us_counter < 1000 ){
    us_counter++;
  } else {
    us_counter = 0;
    if(ms_counter<1000) {
      ms_counter++;
      delay_ms++;
    } else {
      ms_counter = 0;
      if(sec_counter < 1000) {
        sec_counter++;
        delay_sec++;
      } else {
        sec_counter = 0;
      }
    }
  }
}

void Delay_us(uint32_t us) {    //функция задержки на 1 мкс
    delay_us = 0;
    while(delay_us < us)
    {
      __NOP();
     };
    }

    void Delay_ms(uint32_t ms) {    //функция задержки на 1 мкс
    delay_us = 0;
    while(delay_us < ms)
    {
      __NOP();
     };
    }

    void Delay_sec(uint32_t sec) {    //функция задержки на 1 мкс
    delay_us = 0;
    while(delay_us < sec)
    {
      __NOP();
     };
    }

    void delay_us_tim10(uint16_t us_tim10) {
    TIM10->CNT = 0;              // Сбрасываем счетчик
    while (TIM10->CNT < us_tim10);     // Ждем, пока он досчитает до нужного количества мкс
}