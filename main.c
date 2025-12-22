#include <stm32f407xx.h>
#include "log.h"
#include "delay.h"
#include "buttons.h"
#include "usart.h"
#include "modbus_rtu.h"

void RCC_Init(void);

uint8_t modbus_req_rx[256];
uint8_t modbus_rx_len;
uint8_t modbus_err;
uint8_t modbus_answer_tx[256];
uint8_t modbus_answer_len;

void USART6_IRQHandler(void) {
  if(USART6->SR & USART_SR_RXNE) {
    ModbusReception();
  }
  NVIC_ClearPendingIRQ(USART6_IRQn);
}

void TIM2_IRQHandler(void) {
  TIM2->SR &= ~(TIM_SR_UIF);
  ModbusTimersIRQ();
  NVIC_ClearPendingIRQ(TIM2_IRQn);
}

int main(void) {
  LOG_INIT();

  SystemInit();
  RCC_Init();

  __enable_irq();

  LED_init();
  Buttons_init();
  
  TIM2_init();
  USART6_init();
  
  SysTick_Config(SYSTICK_TIMER_CONST);

  GPIO_LED_all_off();

  ModbusTimerStart(DELAY_3_5_BYTE_US);

  while(1) {
    modbus_err = RequestParsingOperationExec();
  }
}

void SysTick_Handler(void)
{
  timer_counter();
}
