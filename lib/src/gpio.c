#include "gpio.h"

void APP_GPIO_Init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	   
	//-------- GPIO settings for LED1 LED2 LED3 --------
	GPIOE -> MODER |= GPIO_MODER_MODER13_0;
	GPIOE -> MODER |= GPIO_MODER_MODER14_0;
	GPIOE -> MODER |= GPIO_MODER_MODER15_0;

	//-------- GPIO for buttons add -------------------
	GPIOE -> PUPDR |= GPIO_PUPDR_PUPDR10_0;
	GPIOE -> PUPDR |= GPIO_PUPDR_PUPDR11_0;
	GPIOE -> PUPDR |= GPIO_PUPDR_PUPDR12_0;
}


/* в байте состояний кнопок выставляются в 1 и сбрасываются в 0 соответствующие биты, при нажатии кнопок
бит 0 - кнопка S1. Если кнопка нажата, то бит равен 1. Если кнопка отпущена, то бит равен 0.
бит 1 - кнопка S2. Если кнопка нажата, то бит равен 1. Если кнопка отпущена, то бит равен 0.
бит 2 - кнопка S3. Если кнопка нажата, то бит равен 1. Если кнопка отпущена, то бит равен 0.

*/


void BTN_Check(uint16_t *ms_count,	// current ms counter value
				uint8_t *BTN_state)
{
	static char S1_cnt, S2_cnt, S3_cnt;

	if ( *ms_count > BTN_CHECK_MS){
		*ms_count = 0;
		// Опрос кнопки S1
		if ((GPIOE->IDR & GPIO_IDR_IDR_10) == 0) {  // if S1 pressed
			if(S1_cnt < BTN_PRESS_CNT){  
				S1_cnt++;
				*BTN_state &= ~(0x01);	// считаем кнопку S1 не нажатой. 
			}
			else *BTN_state |= 0x01;	// считаем кнопку S1 нажатой. выставляем в 1 нулевой бит в байте состояний кнопок
		}
		else{                   // if S1 released
			*BTN_state &= ~(0x01);	// считаем кнопку S1 не нажатой
			S1_cnt = 0;
		}
		
		// Опрос кнопки S2
		if ((GPIOE->IDR & GPIO_IDR_IDR_11) == 0) {  // if S2 pressed
			if(S2_cnt < BTN_PRESS_CNT){
				S2_cnt++;
				*BTN_state &= ~(0x02);
			}
			else *BTN_state |= 0x02;	// выставляем в 1 первый бит в байте состояний кнопок
		}
		else{                   // if S2 released
			*BTN_state &= ~(0x02);
			S2_cnt = 0;
		}
		
		// Опрос кнопки S3
		if ((GPIOE->IDR & GPIO_IDR_IDR_12) == 0) {  // if S3 pressed
			if(S3_cnt < BTN_PRESS_CNT){
				S3_cnt++;
				*BTN_state &= ~(0x04);
			}
			else *BTN_state |= 0x04;
		}
		else{                   // if S3 released
			*BTN_state &= ~(0x04);
			S3_cnt = 0;
		}

	}
 }
