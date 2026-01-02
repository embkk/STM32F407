#include "main.h"
#include <stdio.h>
#include <string.h>

uint16_t us_count=0;
uint16_t ms_cnt=0;
void SysTick_Handler(void){
    timer_counter();
}
int main(void) {
  char ADC_Text[14]    =    "ADC mV = ";
  char DS18B20_Text[12] = {0};
  uint16_t adc_value;
  uint8_t error_1wire = 0;   // 0 = OK, 1 = ERROR;
  uint8_t family_byte = 0; 
  uint8_t ser_number[6] = {};
  uint8_t crc_rx = 0;
  uint8_t scratch_mem[9] = {};
  uint16_t temper;
  uint16_t temper_fract;
  float temper_float;
  RCC_Init();
  ADC_Init();
  TIM10_Init();
  SysTick_Config(8400);

  GPIO_Init();
  LCD1602_PinsInit4bits();
  LCD1602_ScreenInit4bits();
 
  LED1_OFF();
  LED2_OFF();
  LED3_OFF();
    while (1){
      adc_value = (3300*ADC1->DR)/(int)4096;
      sprintf(ADC_Text, "ADC mV = %d   ", adc_value);     
      LCD1602_SetDDRAMAddress(0x00);
      LCD1602_WriteString4bits(ADC_Text, sizeof(ADC_Text));
   //confg settings for DS18B20
      scratch_mem[0]= 0x64;         //TH = 0x64 = 100
      scratch_mem[1]= 0x0A;         //TL = 0x0A = 10 
      scratch_mem[2]= 0x3F;         // config = 0x3F;10-bit temperature format
      WriteScratch(scratch_mem);
      Convert_Temperature(); // convert temperature (Инициируем преобразование температуры)

// Ожидаем завершения преобразования (время SENSOR_CHECK_TIME_US)
      delay_us_tim10(SENSOR_CHECK_TIME_US); 
      error_1wire = ReadScratchpad(scratch_mem); // Считываем данные из scratchpad
      if(error_1wire == OK_1WIRE){              // Если чтение scratchpad успешно
  // Складываем два байта температуры из scratch_mem[1] (MSB) и scratch_mem[0] (LSB)
        temper = ((scratch_mem[1] << 8)) + scratch_mem[0];
        if(temper < 0x0800){ // если положительные температуры (проверяем знаковый бит)
        temper_fract = (((temper & 0x000F)*100) >> 4); // Вычисляем дробную часть
        temper_float = ((float)temper / 16);           // Вычисляем температуру в float
        temper_float = (float)temper / 16;
        sprintf(DS18B20_Text, "temp = %d.%d", (temper >> 4), temper_fract);
        LCD1602_SetDDRAMAddress(0x40);
        LCD1602_WriteString4bits(DS18B20_Text, sizeof(DS18B20_Text));
                         }
      else{ // если отрицательные температуры
        temper = (0xFFFF - temper) + 1;                  // Инвертируем и добавляем 1 (двоичное дополнение)
        temper_fract = (((temper & 0x000F)*100) >> 4); // Вычисляем дробную часть
    // temper_float = ((float)temper / 16);        // Эта строка отсутствует на фото, но логична
        temper_float = (float)temper / 16;
          }
        }
      } 
    } 


/*************************** End of file ****************************/
