#include <stm32f407xx.h>
#include "log.h"
#include "delay.h"
#include "buttons.h"
#include "usart.h"

void RCC_Init(void);

#define LED_BLINK_300ms 300

uint8_t rs485_rx_byte;
char rs485_tx_array[12] = "RS485 RX Ok\n";

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

  LED_init();
  USART6_init();
  
  SysTick_Config(SYSTICK_TIMER_CONST);

  GPIO_LED_all_off();

  while(1) {
    if( USART_receive_byte(USART6, &rs485_rx_byte) == USART_OK ) {
      GPIO_LED_on(LED02);
      Delay_ms(LED_BLINK_300ms);
      GPIO_LED_off(LED02);

      USART_send_bytes(USART6, rs485_tx_array, sizeof(rs485_tx_array));
    }
  }
}

void SysTick_Handler(void)
{
  timer_counter();
}
