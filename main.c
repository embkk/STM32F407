#include <stm32f407xx.h>
#include "log.h"
#include "delay.h"
#include "buttons.h"
#include "usart.h"

void RCC_Init(void);

#define LED_BLINK_300ms 300

int main(void) {
  LOG_INIT();

  SystemInit();
  SysTick_Config(SYSTICK_TIMER_CONST);

  RCC_Init();
  LED_init();

  while(1) {

  }
}





void SysTick_Handler(void)
{

}
