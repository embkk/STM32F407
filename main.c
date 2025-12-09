#include <stm32f407xx.h>
#include <stdlib.h>
#include <stdio.h>
#include "buttons.h"
#include "log.h"
#include "can.h"
#include "usart.h"
#include "gpio.h"
 
void RCC_Init(void);
void Check_CAN(void);

uint16_t can_tx_ms_count = 0;
uint16_t btn_ms_count = 0;

char can_tx_data_bytes[CAN_TX_DATA_LEN] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
char can_rx_data_bytes[CAN_TX_DATA_LEN] = {};
uint16_t can_rx_frame_id = 0;
uint16_t can_rx_data_len = 0;
uint8_t can_err_code = 0;

uint8_t stop_send = 0;
uint8_t stop_receive = 0;

int main(void) {
  LOG_INIT();

  SystemInit();
  SysTick_Config(84000);
  RCC_Init();

  LED_init();
  Buttons_init();
  
  USART_init();
  CAN2_init();

  while(1) {
    Check_CAN();
  }
}

void Check_CAN(void) {
  can_err_code = CAN2_Receive_msg(&can_rx_frame_id, &can_rx_data_len, can_rx_data_bytes);
  if(can_err_code == 0) {
    if(can_rx_frame_id == CAN_RX_FRAME_LED_CONTROL) {
      LOG_MESSAGE("[%d] Received %d %d [%s]", btn_ms_count, can_rx_frame_id, can_rx_data_len, can_rx_data_bytes);  
      GPIO_LED_all_off();
      if(can_rx_data_bytes[0] & 0b001) {
        GPIO_LED_on(LED01);
      }
      if(can_rx_data_bytes[0] & 0b010) {
        GPIO_LED_on(LED02);
      }
      if(can_rx_data_bytes[0] & 0b100) {
        GPIO_LED_on(LED03);
      }
    } else if (can_rx_frame_id == CAN_RX_FRAME_LED_STATE) {
      //LOG_MESSAGE("[%d] Received %d %d [%s]", btn_ms_count, can_rx_frame_id, can_rx_data_len, can_rx_data_bytes);
      //LOG_MESSAGE("[%d] Send response %d [%s]", btn_ms_count, can_rx_frame_id, btn_state);
      CAN2_Send_msg(CAN_TX_FRAME_ID, 3, (char*)btn_state);
    } else if (can_rx_frame_id>0) {
      LOG_MESSAGE("[%d] Received unknown frame %d", btn_ms_count, can_rx_frame_id);  
    }
  } else if(can_err_code>1) {
    //stop_receive = 1;
    LOG_MESSAGE("Receive message error %d", can_err_code);
  }
}




void SysTick_Handler(void)
{
  btn_ms_count++;
  if(btn_ms_count> BTN_CHECK_MS) {
    btn_ms_count=0;
    Buttons_check();
  }
  can_tx_ms_count++;
}
