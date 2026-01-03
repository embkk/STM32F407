#include "delay.h"

uint32_t delay_us;
uint32_t delay_ms;
uint32_t delay_sec;

//uint16_t btn_ms_counter;	// global ms_counter for buttons polling
/******
Функция подсчета микросекунд до 1000 мкс 
подсчета милисекунд до 1000 мс
секунд до 1000 секунд
используется только внутри прерываний SysTick_Handler(void)
которое срабатывает каждую 1 микросекунду
 ******/

 void timer_counter(uint16_t *btn_ms_counter){
	uint16_t static us_counter;
	uint16_t static ms_counter;
	uint16_t static sec_counter;

	if( us_counter < 1000 ){	// us timer
		us_counter++;
		delay_us++;
	}
	else{					// ms timer
		us_counter = 0;
		if(ms_counter < 1000){ 
			ms_counter++;	
			delay_ms++;
			(*btn_ms_counter)++;
		}
		else{				// sec timer
			ms_counter = 0;
			if(sec_counter < 1000){
				sec_counter++;
				delay_sec++;
			}
			else{
				sec_counter = 0;
			}
		}
	}
}

void Delay_us(uint32_t us){		// фунукция задержки на 1 мкс
	delay_us = 0;
	while(delay_us < us){
		__NOP();
	};
}



void Delay_ms(uint32_t ms){		// фунукция задержки на 1 мс
	delay_ms = 0;
	while(delay_ms < ms){
		__NOP();
	};
}


void Delay_sec(uint32_t sec){		// фунукция задержки на 1 мс
	delay_sec = 0;
	while(delay_sec < sec){
		__NOP();
	};
}

