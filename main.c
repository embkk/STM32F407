#include <stm32f407xx.h>
#include "log.h"
#include "gpio.h"
#include "delay.h"
#include "buttons.h"
#include "lcd1602.h"
#include "adc.h"
#include "onewire.h"

#define LCD_REFRESH_RATE 840000
#define SENSOR_REFRESH_RATE 420000

#define SENSOR_CHECK_TIME_MS 300
uint32_t refresh_counter = 0;
uint32_t sensor_refresh_counter = 0;
uint8_t error_1wire = 0;
uint8_t family_byte = 0;
uint8_t ser_number[6] = {};
uint8_t crc_rx = 0;
uint8_t scratch_mem[9] = {};
uint16_t temper;
uint16_t temper_fract;
float temper_float;
char line[16];

void RCC_Init(void);
void check_temp(void);

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
  release_1wire();

  while(1) {
    refresh_counter++;
    sensor_refresh_counter++;

    if(refresh_counter>=LCD_REFRESH_RATE) {
      refresh_counter = 0;

      uint16_t mv = (ADC1->DR * 3300) / 4096;
      sprintf(line, "   ADC mV = %d.%d", mv / 1000, (mv % 1000) / 10);

      LCD1602_SetDDRAMAddress(0x00);
      LCD1602_WriteString4bits((uint8_t*)line, LCD_CHAR_NUM_MAX);

    if(temper < 0x0800) {
        // Положительная температура
        temper_fract = ((temper & 0x000F) * 100) >> 4;
        temper_float = (float)temper / 16.0;
        sprintf(line, "   t = %d.%d    ", (temper >> 4), temper_fract);
    } else {
        // Отрицательная температура
        temper = (0xFFFF - temper) + 1;
        temper_fract = ((temper & 0x000F) * 100) >> 4;
        temper_float = -((float)temper / 16.0);
        sprintf(line, "   t =-%d.%d    ", (temper >> 4), temper_fract);
    }
      
      LCD1602_SetDDRAMAddress(0x40);
      LCD1602_WriteString4bits((uint8_t*)line, LCD_CHAR_NUM_MAX);
    }
    if(sensor_refresh_counter>=SENSOR_REFRESH_RATE) {
      sensor_refresh_counter = 0;
      check_temp();
    }
    
  }
}



void check_temp(void) {
    error_1wire = Read_ROM64(&family_byte, ser_number, &crc_rx);
    if( error_1wire == OK_1WIRE ) {
      LOG_MESSAGE("+++ DS18B20 found +++ \n");
    } else {
      LOG_MESSAGE("---- ERROR: 1-Wire DS18B20 not found \n");
    }
    
    //config
    scratch_mem[0] = 0x64;  //TH = 100
    scratch_mem[1] = 0x0A;  // TL = 10
    scratch_mem[2] = 0x1F;  // 9bit

    Convert_Temperature();

    Delay_ms(SENSOR_CHECK_TIME_MS);

    error_1wire = ReadScratchpad(scratch_mem);
    if(error_1wire == OK_1WIRE) {
      temper = ((scratch_mem[1] << 8 )) + scratch_mem[0];
    }
  }


void SysTick_Handler(void)
{
  timer_counter();
}
