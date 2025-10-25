#ifndef USART_H
#define USART_H

#include "stm32f407xx.h"

extern unsigned char USART_Initialized;

void USART_send_string(USART_TypeDef*, const char*);
void USART_init(void);
void USART1_IRQHandler(void);

#endif