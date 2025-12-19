#ifndef USART_H
#define USART_H

#include "stm32f407xx.h"

#define USART_OK  0
#define USART_ERR 1

extern unsigned char USART_Initialized;

void USART_send_bytes(USART_TypeDef*, const char*, const uint32_t);
void USART_send_string(USART_TypeDef*, const char*);
void USART1_init(void);
void USART6_init(void);

#endif