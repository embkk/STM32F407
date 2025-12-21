#include <stm32f407xx.h>
#include "log.h"
#include "delay.h"
#include "buttons.h"
#include "usart.h"
//#include "modbus_rtu.h"

void RCC_Init(void);


void USART6_IRQHandler(void) {
  if(USART6->SR & USART_SR_RXNE) {
    
  }
  NVIC_ClearPendingIRQ(USART6_IRQn);
}

void TIM2_IRQHandler(void) {
}

int main(void) {
  LOG_INIT();

  SystemInit();
  RCC_Init();

  __enable_irq();

  LED_init();
  USART6_init();
  
  SysTick_Config(SYSTICK_TIMER_CONST);

  GPIO_LED_all_off();

  while(1) {
  }
}

void SysTick_Handler(void)
{
  timer_counter();
}
