#include "delay.h"
#include "cmsis_gcc.h"

  uint16_t us_delay;
  uint16_t ms_delay;
  uint16_t sec_delay;
  uint16_t us_counter;
  uint16_t ms_counter;
  uint16_t sec_counter;
void timer_counter(void) {

  
  us_delay++;
  if(us_counter < 1000 ){
    us_counter++;
  } else {
    us_counter = 0;
    if(ms_counter<1000) {
      ms_counter++;
      ms_delay++;
    } else {
      ms_counter = 0;
      if(sec_counter < 1000) {
        sec_counter++;
        sec_delay++;
      } else {
        sec_counter = 0;
      }
    }
  }
}

void Delay_us(uint32_t us) {
  us_delay = 0;
  while(us_delay < us) {
    __NOP();
  }
}
void Delay_ms(uint32_t ms) {
  ms_delay = 0;
  while(ms_delay < ms) {
    __NOP();
  }

}
void Delay_sec(uint32_t sec) {
  sec_delay = 0;
  while(sec_delay < sec) {
    __NOP();
  }

}