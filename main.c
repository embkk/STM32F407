#include <stm32f407xx.h>
#include <stdlib.h>
#include <stdio.h>
#include "buttons.h"
#include "exti.h"
#include "log.h"
#include "can.h"
#include "usart.h"
 
void RCC_Init(void);

uint16_t can_tx_ms_count = 0;
uint16_t btn_ms_count = 0;

char can_tx_data_bytes[CAN_TX_DATA_LEN] = {11,22,33,44,55,66,77,88};
char can_rx_data_bytes[CAN_TX_DATA_LEN] = {};
uint16_t can_rx_frame_id = 0;
uint16_t can_rx_data_len = 0;
uint8_t can_err_code = 0;

int main(void) {
  LOG_INIT();

  SystemInit();
  SysTick_Config(84000);
  RCC_Init();

  LED_init();
  Buttons_init();
  EXTI_init_lines(10,11,12);
  
  USART_init();
  CAN2_init();

  while(1) {
    //can_tx_data_bytes[0] = ( (B3_state <<2) | (B2_state <<1) | B1_state);
    if(can_tx_ms_count < CAN_TX_TIME_MS) continue;

    can_tx_ms_count=0;
    can_err_code = CAN2_Send_msg(CAN_TX_FRAME_ID, CAN_TX_DATA_LEN, can_tx_data_bytes);
    if(can_err_code != 0) {
      LOG_MESSAGE("Can send message error %d", can_err_code);
    } else {
      LOG_MESSAGE("Can send message success");
    }
    GPIO_LED_toggle(LED01);

    can_err_code = CAN2_Receive_msg(&can_rx_frame_id, &can_rx_data_len, can_rx_data_bytes);

    if(can_rx_frame_id == 0) {
      LOG_MESSAGE("Can RX Frame ID empty");
      continue;
    }
    if(can_err_code == 0) {
      LOG_MESSAGE("Can receive message success");
      USART_send_bytes(USART1, can_rx_data_bytes, can_rx_data_len); 
    } else {
      LOG_MESSAGE("Can receive message error %d", can_err_code);
    }
  }
}

void EXTI15_10_IRQHandler(void) {
  if(btn_ms_count>BTN_THRESHOLD) {
    btn_ms_count = 0;
    /*EXTI_handle(10, callback);
    EXTI_handle(11, callback);
    EXTI_handle(12, callback);*/
  } else {
    EXTI_clear_ps(10);
    EXTI_clear_ps(11);
    EXTI_clear_ps(12);
  }

  NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
}

void SysTick_Handler(void)
{
  btn_ms_count++;
  can_tx_ms_count++;
}
