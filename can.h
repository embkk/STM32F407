#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#define CAN_TX_TIME_MS    3000     // время ожидания отправки сообщения
#define CAN_TX_DATA_LEN   8       // количество байт данных в отправляемом сообщении CAN

#define CAN_RX_FRAME_LED_CONTROL      0x234   // FRAME_ID сообщений, которые мы принимаем, остальные игнорируем
#define CAN_RX_FRAME_LED_STATE 0x432   // FRAME_ID сообщений, которые мы принимаем, остальные игнорируем
#define CAN_TX_FRAME_ID       0x565   // FRAME_ID отправляемого сообщения

void CAN2_init(void);
uint8_t CAN2_Receive_msg(uint16_t*, uint16_t*, char[]);
uint8_t CAN2_Send_msg(const uint16_t, const uint16_t, const char[]);

#endif