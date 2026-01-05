#include <stm32f407xx.h>
#include "log.h"
#include "gpio.h"
#include "delay.h"
#include "buttons.h"
#include "lcd1602.h"
#include "adc.h"

#define LCD_REFRESH_RATE 840000
uint32_t refresh_counter = 0;

void RCC_Init(void);

int main(void) {
  LOG_INIT();
  
  SystemInit();
  RCC_Init();
  Buttons_init();
  LED_init();
  ADC1_Init();

  GPIO_LED_all_off();
  
  LOG_MESSAGE("Start systick...");
  SysTick_Config(SYSTICK_TIMER_CONST);
  LCD1602_PinsInit4bits();
  LCD1602_ScreenInit4bits();
  LOG_MESSAGE("Init completed");

  LCD1602_CursorBlink_OFF();

  while(1) {
    refresh_counter++;
    if(refresh_counter<LCD_REFRESH_RATE) continue;
    refresh_counter = 0;
    
    char line[16] = "";
    
    sprintf(line, "   ADC = %d     ", ADC1->DR);
    LCD1602_SetDDRAMAddress(0x00);
    LCD1602_WriteString4bits((uint8_t*)line, LCD_CHAR_NUM_MAX);

    sprintf(line, "   Ref = %d     ", ADC1->DR);
    LCD1602_SetDDRAMAddress(0x40);
    LCD1602_WriteString4bits((uint8_t*)line, LCD_CHAR_NUM_MAX);
  }
}



void SysTick_Handler(void)
{
  timer_counter();
  
}
