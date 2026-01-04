#ifndef USART_H
#define USART_H

#include "stm32f4xx.h"

//======= USART6 Error codes ================
#define USART6_OK		0
#define USART6_ERR		1

#define USART_OK		0
#define USART_ERR		1





void USART1_Init(void);
void USART2_Init(void);
void USART6_Init(void);




void usart1_send(uint8_t data[], uint16_t len);
void usart2_send(uint8_t data[], uint8_t len);
void usart6_send(uint8_t data[], uint8_t len);


void usart1_send_w32(uint32_t data_w32[], uint16_t len); 



/*******
Функция приема байта по USART с таймаутом
если таймаут не вышел и пришел байт данных, то 
считанный байт выдает в rx_byte а возвращает USART_OK
если таймаут вышел, то ф-ия возвращает USART_ERR
номер модуля USART указывается как входной параметр
*******/
uint8_t usart_receive_byte(uint8_t usart_number, uint8_t *rx_byte);
uint8_t usart2_receive_byte(uint8_t *rx_byte);
uint8_t usart6_receive_byte(uint8_t *rx_byte);


#endif


