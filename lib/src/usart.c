#include "usart.h"




// настройка USART1 для передачи принятых данных в ПК по USART1
void USART1_Init(void){	
	
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;							// включение тактирования GPIOA: PA9 = TX, PA10 = RX
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;							// включение тактирования USART1 от шины APB2

	
	GPIOA -> MODER  |= GPIO_MODER_MODER9_1;							// Альтернативная функция для PA9 (USART1 - TX)
	GPIOA -> AFR[1] |= (7 << GPIO_AFRH_AFSEL9_Pos );					// AF7 для PA9
	GPIOA -> MODER  |= GPIO_MODER_MODER10_1;                           // Альтернативная функция для PA10 (USART1 - RX)
	GPIOA -> AFR[1] |= (7 << GPIO_AFRH_AFSEL10_Pos );					// AF7 для PA10

	
	/* Расчет скорости передачи данных:
		(84МГц/115200)/16 = 45.57; 
		Целая часть = 45 = 0x2D; 
		Дробная часть = 0.57*16 = 9 = 0x09 
	*/
	USART1 -> BRR |= 0x2D9;	// 115200

	/* Расчет скорости передачи данных:
		(42МГц/115200)/16 = 22.79; 
		Целая часть = 22 = 0x16; 
		Дробная часть = 0.79*16 = 12 = 0x0C
	*/
	//USART1 -> BRR |= 0x16C;	// 115200 APB2 freq = 42 MHz
	
	USART1 -> CR1 |= USART_CR1_TE | USART_CR1_RE;					// Включение приемника и передатчика
	USART1 -> CR1 &= ~(USART_CR1_M) | ~(USART_CR1_PCE);              // 8-бит, без контроля четности
	USART1 -> CR2 &= ~(USART_CR2_STOP);                              // 1 стоповый бит
	USART1 -> CR1 |= USART_CR1_UE;                                   // Включение USART1

}



// настройка USART2 
void USART2_Init(void){	
	
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN;							// включение тактирования GPIOD: PD6 = RX, PD5 = TX
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;							// включение тактирования USART6 от шины APB2

	
	GPIOD -> MODER  |= GPIO_MODER_MODER5_1;							// Альтернативная функция для PD5 (USART2 - TX)
	GPIOD -> AFR[0] |= (7 << GPIO_AFRL_AFSEL5_Pos);					// AF7 для PD5
	GPIOD -> MODER  |= GPIO_MODER_MODER6_1;                           // Альтернативная функция для PD6 (USART2 - RX)
	GPIOD -> AFR[0] |= (7 << GPIO_AFRL_AFSEL6_Pos);					// AF7 для PD6

	
	/* Расчет скорости передачи данных:
		(84МГц/115200)/16 = 45.57; 
		Целая часть = 45 = 0x2D; 
		Дробная часть = 0.57*16 = 9 = 0x09 
	*/

	USART2 -> BRR |= 0x2D9;	// 115200
	//USART2 -> BRR |= 0x222E;	// 9600	
	
	USART2 -> CR1 |= USART_CR1_TE | USART_CR1_RE;					// Включение приемника и передатчика
	USART2 -> CR1 &= ~(USART_CR1_M) | ~(USART_CR1_PCE);              // 8-бит, без контроля четности
	USART2 -> CR2 &= ~(USART_CR2_STOP);                              // 1 стоповый бит
	USART2 -> CR1 |= USART_CR1_UE;                                   // Включение USART2

}





// настройка USART6 
void USART6_Init(void){	
	
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;							// включение тактирования GPIOC: PC6 = TX, PC7 = RX
	RCC -> APB2ENR |= RCC_APB2ENR_USART6EN;							// включение тактирования USART6 от шины APB2

	
	GPIOC -> MODER  |= GPIO_MODER_MODER6_1;							// Альтернативная функция для PC6 (USART1 - TX)
	GPIOC -> AFR[0] |= (8 << GPIO_AFRL_AFSEL6_Pos);					// AF8 для PC6
	GPIOC -> MODER  |= GPIO_MODER_MODER7_1;                           // Альтернативная функция для PC7 (USART1 - RX)
	GPIOC -> AFR[0] |= (8 << GPIO_AFRL_AFSEL7_Pos);					// AF8 для PC7

	
	/* Расчет скорости передачи данных:
		(84МГц/115200)/16 = 45.57; 
		Целая часть = 45 = 0x2D; 
		Дробная часть = 0.57*16 = 9 = 0x09 
	*/

	USART6 -> BRR |= 0x2D9;	// 115200
	
	USART6 -> CR1 |= USART_CR1_TE | USART_CR1_RE;					// Включение приемника и передатчика
	USART6 -> CR1 &= ~(USART_CR1_M) | ~(USART_CR1_PCE);              // 8-бит, без контроля четности
	USART6 -> CR2 &= ~(USART_CR2_STOP);                              // 1 стоповый бит
	USART6 -> CR1 |= USART_CR1_UE;                                   // Включение USART6

}



void usart1_send(uint8_t data[], uint16_t len) {
	for (uint16_t i=0; i < len; i++){
		USART1 -> DR = data[i];
		while ((USART1 -> SR & USART_SR_TXE) == 0){};
	}
}


void usart1_send_w32(uint32_t data_w32[], uint16_t len){
	for( uint16_t i= 0; i < len; i++ ){	// data word selectcion
		for( uint8_t j = 0; j < 32/8; j++ ){	// byte in word selection. first send LSB. Last send MSB/
			uint32_t tx_byte = (( data_w32[i] >> ( j*8 )) & 0x000000FF);
			USART1 -> DR = (uint8_t)tx_byte;
			while ((USART1 -> SR & USART_SR_TXE) == 0){};
		}
	}
}

void usart2_send(uint8_t data[], uint8_t len) {
	for (uint8_t i=0; i < len; i++){
		USART2 -> DR = data[i];
		while ((USART2 -> SR & USART_SR_TXE) == 0){};
	}
}



void usart6_send(uint8_t data[], uint8_t len) {
	for (uint8_t i=0; i < len; i++){
		USART6 -> DR = data[i];
		while ((USART6 -> SR & USART_SR_TXE) == 0){};
	}
}


uint8_t usart_receive_byte(uint8_t usart_number, uint8_t *rx_byte){
	uint8_t timer = 0;
	
	switch(usart_number){
	case 1:
		while(!(USART1->SR & USART_SR_RXNE)){
			if(timer < 32) timer++;
			else return USART_ERR;
		}	
		*rx_byte = USART1 -> DR;
		return USART_OK;
		break;
	
	case 2:
		while(!(USART2->SR & USART_SR_RXNE)){
			if(timer < 32) timer++;
			else return USART_ERR;
		}	
		*rx_byte = USART2 -> DR;
		return USART_OK;
		break;
	
	case 6:
		while(!(USART6->SR & USART_SR_RXNE)){
			if(timer < 32) timer++;
			else return USART_ERR;
		}	
		*rx_byte = USART6 -> DR;
		return USART_OK;
		break;
	
	default: 
		__NOP();
	}
	
	
}


uint8_t usart2_receive_byte(uint8_t *rx_byte){
	uint8_t timer = 0;
	while(!(USART2->SR & USART_SR_RXNE)){
		if(timer < 32) timer++;
		else return USART_ERR;
	}	
	*rx_byte = USART2 -> DR;
	return USART_OK;
}



uint8_t usart6_receive_byte(uint8_t *rx_byte){
	uint8_t timer = 0;
	while(!(USART6->SR & USART_SR_RXNE)){
		if(timer < 32) timer++;
		else return USART_ERR;
	}	
	*rx_byte = USART6 -> DR;
	return USART_OK;
}

//retarget the C library printf function to the USART1 
int __SEGGER_RTL_X_file_write(__SEGGER_RTL_FILE *__stream, const char *__s, unsigned __len) {
  
  // Send string over USART1 in pending mode 
  for (; __len != 0; --__len) {
    USART1->DR = * __s++;
    while (RESET == READ_BIT(USART1->SR, USART_SR_TXE));
  } 

  return 0;
  }
