#ifndef GPIO_H
#define GPIO_H

#include "stm32f4xx.h"

#define LED1_PORT	GPIOE
#define LED2_PORT	GPIOE
#define LED3_PORT	GPIOE

#define LED1_PIN_NUM	13
#define LED2_PIN_NUM	14
#define LED3_PIN_NUM	15


#define LED1_ON()		(LED1_PORT -> BSRR |= 1 << (LED1_PIN_NUM + 16))
#define LED2_ON()		(LED2_PORT -> BSRR |= 1 << (LED2_PIN_NUM + 16))
#define LED3_ON()		(LED3_PORT -> BSRR |= 1 << (LED3_PIN_NUM + 16))

#define LED1_OFF()		(LED1_PORT -> BSRR |= 1 << LED1_PIN_NUM)
#define LED2_OFF()		(LED2_PORT -> BSRR |= 1 << LED2_PIN_NUM)
#define LED3_OFF()		(LED3_PORT -> BSRR |= 1 << LED3_PIN_NUM)

#define LED1_TOGGLE()	(LED1_PORT -> ODR ^= (1 << LED1_PIN_NUM))
#define LED2_TOGGLE()	(LED2_PORT -> ODR ^= (1 << LED2_PIN_NUM))
#define LED3_TOGGLE()	(LED3_PORT -> ODR ^= (1 << LED3_PIN_NUM))


#define LED1_CHECK()	( LED1_PORT->ODR & ( 1 << LED1_PIN_NUM) )
#define LED2_CHECK()	( LED2_PORT->ODR & ( 1 << LED2_PIN_NUM) )
#define LED3_CHECK()	( LED3_PORT->ODR & ( 1 << LED3_PIN_NUM) )

//------------ buttons add----------------

#define BTN_PORT		GPIOE
#define BTN1_PIN_NUM	10
#define BTN2_PIN_NUM	11
#define BTN3_PIN_NUM	12


#define BTN_CHECK_MS		10		// период опроса кнопок в мс
#define	BTN_PRESS_CNT		4		// кол-во последовательных проверок состояния кнопки


void APP_GPIO_Init(void);

void BTN_Check(uint16_t *ms_count,	uint8_t *BTN_state);


#endif