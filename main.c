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

uint8_t line1_text[LCD_CHAR_NUM_MAX] = "  BTN3 BTN2 BTN1";
uint8_t line2_text[8][LCD_CHAR_NUM_MAX] = {
                              "  0    0    0   ",
                              "  0    0    1   ",
                              "  0    1    0   ",
                              "  0    1    1   ",
                              "  1    0    0   ",
                              "  1    0    1   ",
                              "  1    1    0   ",
                              "  1    1    1   ",
                            };

/*void on_btn_pressed(void) {
  LOG_MESSAGE("Callback - button Pressed");
  Buttons_print();
}

void on_btn_released(void) {
  LOG_MESSAGE("Callback - button Released");
  Buttons_print();
}*/

void on_btn_event(void) {
  uint8_t value = (btn_state[2] << 2) | (btn_state[1] << 1) | btn_state[0];

  LCD1602_SetDDRAMAddress(0x00);
  LCD1602_WriteString4bits(line1_text, LCD_CHAR_NUM_MAX);
  LCD1602_SetDDRAMAddress(0x40);
  LCD1602_WriteString4bits(line2_text[value], LCD_CHAR_NUM_MAX);
  
  LCD1602_CursorBlink_OFF();

  if(btn_state[0]) {
    LCD1602_CursorBlink_ON();
    LCD1602_SetDDRAMAddress(0x4D);
    GPIO_LED_on(LED01);
  } else {
    GPIO_LED_off(LED01);
  }


  if(btn_state[1]) {
    LCD1602_CursorBlink_ON();
    LCD1602_SetDDRAMAddress(0x47);
    GPIO_LED_on(LED02);
  } else {
    GPIO_LED_off(LED02);
  }

  if(btn_state[2]) {
    LCD1602_CursorBlink_ON();
    LCD1602_SetDDRAMAddress(0x41);
    GPIO_LED_on(LED03);
  } else {
    GPIO_LED_off(LED03);
  }

}



int main(void) {
  LOG_INIT();
  
  SystemInit();
  RCC_Init();
  Buttons_init();
  LED_init();

  GPIO_LED_all_off();
  Event_AddListener(btn_pressed, on_btn_event);
  Event_AddListener(btn_released, on_btn_event);
  
  LOG_MESSAGE("Start systick...");
  SysTick_Config(SYSTICK_TIMER_CONST);
  LCD1602_PinsInit4bits();
  LCD1602_ScreenInit4bits();
  LOG_MESSAGE("Init completed");

  while(1) {
      //GPIO_LED_all_off();
      //on_btn_event();
      //Delay_sec(1);
      //GPIO_LED_all_on();
      //Delay_sec(1);
      
      Buttons_check();
  }
}



void SysTick_Handler(void)
{
  timer_counter();
  
}
