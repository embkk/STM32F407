#include <stm32f407xx.h>
#include "log.h"
#include "gpio.h"
#include "delay.h"
#include "buttons.h"
#include "lcd1602.h"

void RCC_Init(void);

// BTN3   BTN2   BTN1   
//  0      1       0

//  0 или 1 состояние кнопок нажата
//  включение курсора
//  позиционирование на кнопке
//  включение режима мигания курсора

uint8_t line1_text[LCD_CHAR_NUM_MAX] = "BTN3 BTN2 BTN1";
uint8_t line2_text[8][LCD_CHAR_NUM_MAX] = {
                              "0 0 0",
                              "0 0 1",
                              "0 1 0",
                              "0 1 1",
                              "1 0 0",
                              "1 0 1",
                              "1 1 0",
                              "1 1 1",
                            };

void on_btn_pressed(void) {
  LOG_MESSAGE("Callback - button Pressed");
  Buttons_print();
}

void on_btn_released(void) {
  LOG_MESSAGE("Callback - button Released");
  Buttons_print();
}

int main(void) {
  LOG_INIT();
  
  SystemInit();
  RCC_Init();
  Buttons_init();
  LED_init();

  SysTick_Config(SYSTICK_TIMER_CONST);

  GPIO_LED_all_off();

  Event_AddListener(btn_pressed, on_btn_pressed);
  Event_AddListener(btn_released, on_btn_released);

  LOG_MESSAGE("Init completed");
  
  //LCD1602_PinsInit4bits();
  //LCD1602_ScreenInit4bits();

  while(1) {
  }
}



void SysTick_Handler(void)
{
  Buttons_check();
  timer_counter();
}
