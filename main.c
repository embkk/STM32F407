#include <stm32f407xx.h>
#include "log.h"
#include "delay.h"
void RCC_Init(void);


int main(void) {
  LOG_INIT();

  SystemInit();
  RCC_Init();

  SysTick_Config(SYSTICK_TIMER_CONST);

  while(1) {
  }
}

void SysTick_Handler(void)
{
  timer_counter();
}
